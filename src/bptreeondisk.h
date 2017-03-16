#ifndef BPTREEONDISK_H
#define BPTREEONDISK_H


#include <vector>
#include "mapbptreedef.h"

namespace engine
{

namespace util
{

// In-memory data chunk.
template<class V>
class MapBPTreeOnDiskChunk
{
public:
        const V&                read(const ptr_t& ptr) const;
        void                    write(const ptr_t& ptr, const V& value);
        void                    resize(dsize_t s);
        dsize_t                 size() const;
private:
};

// In-memory chunk.
template<class V>
const V&
MapBPTreeOnDiskChunk<V>::read(const ptr_t& ptr) const
{
}

template<class V>
void
MapBPTreeOnDiskChunk<V>::write(const ptr_t& ptr, const V& value)
{
}

template<class V>
void
MapBPTreeOnDiskChunk<V>::resize(dsize_t s)
{
}

template<class V>
dsize_t
MapBPTreeOnDiskChunk<V>::size() const
{
}




// In-memory tree.
template<class K> struct MapBPTreeNode;

template<class K>
class MapBPTreeOnDiskTree
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
};

// In-memory tree node.
template<class K>
csize_t
MapBPTreeOnDiskTree<K>::get_node_size(const binode_t& node) const
{
}

template<class K>
void
MapBPTreeOnDiskTree<K>::set_node_size(const binode_t& node, csize_t s)
{
}

template<class K>
const MapBPTreeNode<K>&
MapBPTreeOnDiskTree<K>::read(const binode_t& node) const
{
}

template<class K>
void
MapBPTreeOnDiskTree<K>::write(const binode_t& node, const MapBPTreeNode<K>& value)
{
}

template<class K>
bool
MapBPTreeOnDiskTree<K>::less_than(const K& key, const binode_t& node)
{
}

template<class K>
bool
MapBPTreeOnDiskTree<K>::equals(const K& key, const binode_t& node)
{
}

template<class K>
void
MapBPTreeOnDiskTree<K>::resize(dsize_t s)
{
}

template<class K>
dsize_t
MapBPTreeOnDiskTree<K>::size() const
{
}

}

}

#endif // BPTREEONDISK_H
