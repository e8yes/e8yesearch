#ifndef MAPBPTREE_H
#define MAPBPTREE_H

#include <string>
#include <vector>
#include <cstdint>

namespace util
{

typedef uint16_t        csize_t;
typedef uint32_t        dsize_t;
typedef dsize_t         binode_t;
typedef dsize_t         ptr_t;


// In-memory data chunk.
template<class V>
class MapBPTreeInMemoryChunk
{
public:
        const V&                read(const ptr_t& ptr) const;
        void                    write(const ptr_t& ptr, const V& value);
        void                    resize(dsize_t s);
        dsize_t                 size() const;
private:
        std::vector<V>          m_chunk;
};

template<class V>
const V&
MapBPTreeInMemoryChunk<V>::read(const ptr_t& ptr) const
{
        return m_chunk[ptr];
}

template<class V>
void
MapBPTreeInMemoryChunk<V>::write(const ptr_t& ptr, const V& value)
{
        m_chunk[ptr] = value;
}

template<class V>
void
MapBPTreeInMemoryChunk<V>::resize(dsize_t s)
{
        m_chunk.resize(s);
}

template<class V>
dsize_t
MapBPTreeInMemoryChunk<V>::size() const
{
        return m_chunk.size();
}

// In-memory tree.
template<class K> struct MapBPTreeNode;

template<class K>
class MapBPTreeInMemoryTree
{
public:
        const MapBPTreeNode<K>&         read(const binode_t& node) const;
        void                            write(const binode_t& node, const MapBPTreeNode<K>& value);
        void                            resize(dsize_t s);
        dsize_t                         size() const;
private:
        std::vector<MapBPTreeNode<K>>      m_nodes;
};

template<class K>
const MapBPTreeNode<K>&
MapBPTreeInMemoryTree<K>::read(const binode_t& node) const
{
        return m_nodes[node];
}

template<class K>
void
MapBPTreeInMemoryTree<K>::write(const binode_t& node, const MapBPTreeNode<K>& value)
{
        m_nodes[node] = value;
}

template<class K>
void
MapBPTreeInMemoryTree<K>::resize(dsize_t s)
{
        m_nodes.resize(s);
}

template<class K>
dsize_t
MapBPTreeInMemoryTree<K>::size() const
{
        return m_nodes.size();
}

// B+ Tree Map.
template<class K>
struct MapBPTreeNode
{
        K               key;
        csize_t         csize;
        ptr_t           ptr;
};

template<class K, class V, csize_t b=5, class Tree=MapBPTreeInMemoryTree<K>, class Chunk=MapBPTreeInMemoryChunk<V>>
class MapBPTree
{
private:
        class Iterator
        {
        public:
                Iterator& 	operator++();
                bool 		operator==(const Iterator& rhs) const;
                bool 		operator!=(const Iterator& rhs) const;

                bool 		operator*() const;
                bool 		operator->() const;
        };

public:
        MapBPTree(Tree& tree, Chunk& chunk);
        MapBPTree(const MapBPTree& rhs);
        MapBPTree(Tree& tree, Chunk& chunk, const std::vector<std::pair<K, V>>& sorted_entries);

        Iterator                insert(const std::vector<std::pair<K, V>>& entries);
        Iterator                insert(const std::pair<K, V>& entry);
        Iterator                find(const K& key) const;
        Iterator                find(const K& lower, const K& upper) const;
        void                    erase(const Iterator& it);

        unsigned                size() const;
        bool                    empty() const;

        Iterator                begin();
        Iterator                end();
private:
        bool                    is_root(binode_t node) const;
        bool                    is_exterior(binode_t node) const;
        unsigned                parent(binode_t node) const;
        unsigned                child(binode_t node, unsigned i_child) const;

        void                    allocate(binode_t node);
        void                    free(binode_t node);

        MapBPTreeNode<K>*       lookup(const K& key, binode_t& p);

        Tree&                   m_tree;
        Chunk&                  m_chunk;
};

// Helpers.
template<class K, class V, csize_t b, class Tree, class Chunk>
bool
MapBPTree<K, V, b, Tree, Chunk>::is_root(binode_t node) const
{
        return node == 0;
}

template<class K, class V, csize_t b, class Tree, class Chunk>
bool
MapBPTree<K, V, b, Tree, Chunk>::is_exterior(binode_t node) const
{
        return b*node + 1 >= m_chunk.size();
}

template<class K, class V, csize_t b, class Tree, class Chunk>
unsigned
MapBPTree<K, V, b, Tree, Chunk>::parent(binode_t node) const
{
        return node/b;
}

template<class K, class V, csize_t b, class Tree, class Chunk>
unsigned
MapBPTree<K, V, b, Tree, Chunk>::child(binode_t node, unsigned i_child) const
{
        return b*node + i_child + 1;
}

template<class K, class V, csize_t b, class Tree, class Chunk>
void
MapBPTree<K, V, b, Tree, Chunk>::allocate(binode_t node)
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
void
MapBPTree<K, V, b, Tree, Chunk>::free(binode_t node)
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
MapBPTreeNode<K>*
MapBPTree<K, V, b, Tree, Chunk>::lookup(const K& key, binode_t& p)
{
        unsigned node = 0;
        while (!is_exterior(node)) {
                for (unsigned i = node; i < node + b; i ++) {
                        const MapBPTreeNode<K>& e = m_tree.read(i);
                        if (e.key < key) {
                                node = child(node, i);
                                goto next_round;
                        }
                }
                node = child(node, b);
next_round:;
        }
}

// Definitions.
template<class K, class V, csize_t b, class Tree, class Chunk>
MapBPTree<K, V, b, Tree, Chunk>::MapBPTree(Tree& tree, Chunk& chunk):
        m_tree(tree), m_chunk(chunk)
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
MapBPTree<K, V, b, Tree, Chunk>::MapBPTree(const MapBPTree& rhs):
        m_tree(rhs.m_tree), m_chunk(rhs.m_chunk)
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
MapBPTree<K, V, b, Tree, Chunk>::MapBPTree(Tree& tree, Chunk& chunk,
                                           const std::vector<std::pair<K, V>>& sorted_entries):
        m_tree(tree), m_chunk(chunk)
{
        // m_chunk.insert(m_chunk.begin(), sorted_entries.begin(), sorted_entries.end());
        // @todo: use per element insertion for now.
        for (auto it = sorted_entries.begin(); it != sorted_entries.end(); ++ it)
                insert(*it);
}

template<class K, class V, csize_t b, class Tree, class Chunk>
unsigned
MapBPTree<K, V, b, Tree, Chunk>::size() const
{
        return m_chunk.size();
}

template<class K, class V, csize_t b, class Tree, class Chunk>
bool
MapBPTree<K, V, b, Tree, Chunk>::empty() const
{
        return m_chunk.size() == 0;
}

template<class K, class V, csize_t b, class Tree, class Chunk>
typename MapBPTree<K, V, b, Tree, Chunk>::Iterator
MapBPTree<K, V, b, Tree, Chunk>::insert(const std::pair<K, V>& entry)
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
typename MapBPTree<K, V, b, Tree, Chunk>::Iterator
MapBPTree<K, V, b, Tree, Chunk>::insert(const std::vector<std::pair<K, V>>& sorted_entries)
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
typename MapBPTree<K, V, b, Tree, Chunk>::Iterator
MapBPTree<K, V, b, Tree, Chunk>::find(const K& key) const
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
typename MapBPTree<K, V, b, Tree, Chunk>::Iterator
MapBPTree<K, V, b, Tree, Chunk>::find(const K& lower, const K& upper) const
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
void
MapBPTree<K, V, b, Tree, Chunk>::erase(const Iterator& it)
{
}


// Iterators.
template<class K, class V, csize_t b, class Tree, class Chunk>
typename MapBPTree<K, V, b, Tree, Chunk>::Iterator
MapBPTree<K, V, b, Tree, Chunk>::begin()
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
typename MapBPTree<K, V, b, Tree, Chunk>::Iterator
MapBPTree<K, V, b, Tree, Chunk>::end()
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
typename MapBPTree<K, V, b, Tree, Chunk>::Iterator&
MapBPTree<K, V, b, Tree, Chunk>::Iterator::operator++()
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
bool
MapBPTree<K, V, b, Tree, Chunk>::Iterator::operator==(const Iterator& rhs) const
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
bool
MapBPTree<K, V, b, Tree, Chunk>::Iterator::operator!=(const Iterator& rhs) const
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
bool
MapBPTree<K, V, b, Tree, Chunk>::Iterator::operator*() const
{
}

template<class K, class V, csize_t b, class Tree, class Chunk>
bool
MapBPTree<K, V, b, Tree, Chunk>::Iterator::operator->() const
{
}

}

#endif // MAPBPTREE_H
