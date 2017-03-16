#ifndef BPTREEINMEMORY_H
#define BPTREEINMEMORY_H

#include <vector>
#include "mapbptreedef.h"

namespace engine
{
namespace util
{

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

// In-memory chunk.
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
        csize_t				get_node_size(const binode_t& node) const;
        void				set_node_size(const binode_t& node, csize_t s);
        const MapBPTreeNode<K>&         read(const binode_t& node) const;
        void                            write(const binode_t& node, const MapBPTreeNode<K>& value);
        bool				less_than(const K& key, const binode_t& node);
        bool				equals(const K& key, const binode_t& node);
        void                            resize(dsize_t s);
        dsize_t                         size() const;
private:
        std::vector<MapBPTreeNode<K>>   m_nodes;
        std::vector<csize_t>		m_sizes;
};

// In-memory tree node.
template<class K>
csize_t
MapBPTreeInMemoryTree<K>::get_node_size(const binode_t& node) const
{
        return m_sizes[node];
}

template<class K>
void
MapBPTreeInMemoryTree<K>::set_node_size(const binode_t& node, csize_t s)
{
        m_sizes[node] = s;
}

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
bool
MapBPTreeInMemoryTree<K>::less_than(const K& key, const binode_t& node)
{
        return key < m_nodes[node].key;
}

template<class K>
bool
MapBPTreeInMemoryTree<K>::equals(const K& key, const binode_t& node)
{
        return key == m_nodes[node].key;
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


}

}


#endif // BPTREEINMEMORY_H
