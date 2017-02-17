#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <vector>
#include <string>


namespace engine
{

class SearchResult
{
public:
        SearchResult(const std::string& url, const std::string& heading, float importance);

        const std::string& get_url() const;
        const std::string& get_heading() const;
        float get_importance() const;

        bool operator<(const SearchResult& rhs) const;
private:
        const std::string m_url;
        const std::string m_heading;
        const float m_importance;
};

typedef std::vector<SearchResult> sorted_results_t;

};

#endif // SEARCHRESULT_H
