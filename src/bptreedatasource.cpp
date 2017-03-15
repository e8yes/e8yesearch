#include "utils.h"
#include "bptreedatasource.h"


engine::BPTreeDataSource::BPTreeDataSource()
{
}

engine::BPTreeDataSource::~BPTreeDataSource()
{
}

void
engine::BPTreeDataSource::destroy()
{
}

void
engine::BPTreeDataSource::add_documents(const std::vector<Document>& docs)
{
}

void
engine::BPTreeDataSource::find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs)
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

engine::Term*
engine::BPTreeDataSource::find_term_by_content(const std::string& content)
{
}

engine::Term*
engine::BPTreeDataSource::find_term_by_fuzzy_content(const std::string& content)
{
}
