#include "utils.h"
#include "bptreedatasource.h"


namespace engine
{

#define TREE		util::MapBPTreeInMemoryTree
#define CHUNK		util::MapBPTreeInMemoryChunk
#define BREADTH		1024

struct BPTreeDataSource::InternalData
{
        // Document entity.
        struct DocumentKey
        {
                unsigned did;

                bool operator<(const DocumentKey& rhs) const
                {
                        return did < rhs.did;
                }

                bool operator==(const DocumentKey& rhs) const
                {
                        return did == rhs.did;
                }
        };

        struct DocumentSecondaryKey
        {
                engine::doc_id_t	hash_id;
                std::string             uri;

                bool operator<(const DocumentSecondaryKey& rhs)
                {
                        return hash_id != rhs.hash_id ? hash_id < rhs.hash_id : uri< rhs.uri;
                }

                bool operator==(const DocumentSecondaryKey& rhs)
                {
                        return hash_id == rhs.hash_id && uri == rhs.uri;
                }
        };

        struct DocumentValue
        {
                std::string	url;
                unsigned        date;
                unsigned	ndeg;
        };

        TREE<DocumentKey>                       m_doctree;
        TREE<DocumentSecondaryKey>              m_doctree2;
        CHUNK<DocumentValue>                    m_docchunk;
        util::MapBPTree<DocumentKey,
                        DocumentValue,
                        BREADTH,
                        TREE<DocumentKey>,
                        CHUNK<DocumentValue>>   m_docs;
        util::MapBPTree<DocumentSecondaryKey,
                        DocumentValue,
                        BREADTH,
                        TREE<DocumentSecondaryKey>,
                        CHUNK<DocumentValue>>   m_docs_index;

        // Term entity.
        struct TermKey
        {
                unsigned        tid;

                bool operator<(const TermKey& rhs) const
                {
                        return tid < rhs.tid;
                }

                bool operator==(const TermKey& rhs) const
                {
                        return tid == rhs.tid;
                }
        };

        struct TermSecondaryKey
        {
                doc_id_t	hash_id;
                std::string	content;

                bool operator<(const TermSecondaryKey& rhs) const
                {
                        return hash_id != rhs.hash_id ? hash_id < rhs.hash_id : content < rhs.content;
                }

                bool operator==(const TermSecondaryKey& rhs) const
                {
                        return hash_id == rhs.hash_id && content == rhs.content;
                }
        };

        struct TermValue
        {
                unsigned        idf;
        };

        TREE<TermKey>                           m_termtree;
        TREE<TermSecondaryKey>                  m_termtree2;
        CHUNK<TermValue> 			m_termchunk;
        util::MapBPTree<TermKey,
                        TermValue,
                        BREADTH,
                        TREE<TermKey>,
                        CHUNK<TermValue>>	m_terms;
        util::MapBPTree<TermSecondaryKey,
                        TermValue,
                        BREADTH,
                        TREE<TermSecondaryKey>,
                        CHUNK<TermValue>>	m_terms_index;

        // Bag of words entity.
        struct BOWKey
        {
                unsigned did;
                unsigned tid;

                bool operator<(const BOWKey& rhs) const
                {
                        return did == rhs.did ? tid < rhs.tid : did < rhs.did;
                }

                bool operator==(const BOWKey& rhs) const
                {
                        return did == rhs.did && tid == rhs.tid;
                }
        };

        struct BOWValue
        {
                unsigned tf;
        };

        TREE<BOWKey>                            m_bowtree;
        CHUNK<BOWValue>                         m_bowchunk;
        util::MapBPTree<BOWKey,
                        BOWValue,
                        BREADTH,
                        TREE<BOWKey>,
                        CHUNK<BOWValue>>	m_bow;

        // Postings list entity.
        struct PLKey
        {
                unsigned did;
                unsigned tid;

                bool operator<(const BOWKey& rhs) const
                {
                        return did == rhs.did ? tid < rhs.tid : did < rhs.did;
                }

                bool operator==(const BOWKey& rhs) const
                {
                        return did == rhs.did && tid == rhs.tid;
                }
        };

        struct PLValue
        {
                unsigned        pos;
                float           weight;
        };

        InternalData():
                m_docs(m_doctree, m_docchunk),
                m_docs_index(m_doctree2, m_docchunk),
                m_terms(m_termtree, m_termchunk),
                m_terms_index(m_termtree2, m_termchunk),
                m_bow(m_bowtree, m_bowchunk)
        {
        }
};

}

engine::BPTreeDataSource::BPTreeDataSource()
{
        m_dataimpl = new InternalData();
}

engine::BPTreeDataSource::~BPTreeDataSource()
{
        delete m_dataimpl;
}

void
engine::BPTreeDataSource::destroy()
{
}

void
engine::BPTreeDataSource::add_document(const Document& doc)
{
}

void
engine::BPTreeDataSource::find_documents_by_terms(const std::vector<Term>& terms, std::set<Document>& docs)
{
}

void
engine::BPTreeDataSource::force_transaction()
{
}

unsigned
engine::BPTreeDataSource::document_count()
{
}


bool
engine::BPTreeDataSource::find_term_by_content(const std::string& content, Term& term)
{
}

bool
engine::BPTreeDataSource::find_term_by_fuzzy_content(const std::string& content, Term& term)
{
}

void
engine::BPTreeDataSource::fill_bag_of_words(IBagOfWords* bow)
{
}
