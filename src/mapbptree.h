#ifndef MAPBPTREE_H
#define MAPBPTREE_H

#include <string>
#include <vector>
#include <cstdint>

#include "mapbptreedef.h"
#include "bptreeinmemory.h"
#include "bptreeondisk.h"

namespace engine
{

namespace util
{

// B+ Tree Map.
template<class K>
struct MapBPTreeNode
{
        K               key;
        ptr_t           ptr;
};

template<class K, class V, csize_t b=5, class Tree=MapBPTreeInMemoryTree<K>, class Chunk=MapBPTreeInMemoryChunk<V>>
class MapBPTree
{
private:
        class Iterator
        {
        public:
                Iterator(binode_t n_start, dsize_t offset, const K& s, const K& e);

                Iterator& 	operator++();
                bool 		operator==(const Iterator& rhs) const;
                bool 		operator!=(const Iterator& rhs) const;

                bool 		operator*() const;
                bool 		operator->() const;
        private:
                binode_t	n_start;
                dsize_t		offset;

                K		s;
                K		e;
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

        bool 			lookup(const K& key, binode_t& p, csize_t& ib) const;

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
bool
MapBPTree<K, V, b, Tree, Chunk>::lookup(const K& key, binode_t& p, csize_t& ib) const
{
        unsigned node = 0;
        csize_t i = 0;
        while (true) {
                unsigned next;
                unsigned i;
                for (i = 0; i < b; i ++) {
                        if (!m_tree.less_than(key, node + i)) {
                                next = child(node, i);
                                goto next_round;
                        }
                }
                next = child(node, node + i);
next_round:;
                if (is_exterior(node))  break;
                else                    node = next;
        }
        p = node;
        ib = i;
        if (i == 0)
                // Invalid position.
                return false;
        else {
                if (m_tree.equals(key, node + i - 1)) {
                        // Valid but key is unequal.
                        return true;
                } else {
                        // Equal key.
                        return true;
                }
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
MapBPTree<K, V, b, Tree, Chunk>::Iterator::Iterator(binode_t n_start, dsize_t offset, const K& s, const K& e):
        n_start(n_start), offset(offset), s(s), e(e)
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

}

#endif // MAPBPTREE_H
