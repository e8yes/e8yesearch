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
