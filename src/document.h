#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

namespace engine
{

class Document
{
public:
        Document(const std::string& url, const std::string& heading, float importance);

        const std::string& get_url() const;
        const std::string& get_heading() const;
        float get_importance() const;

        bool operator<(const Document& rhs) const;
private:
        const std::string m_url;
        const std::string m_heading;
        const float m_importance;
};

};

#endif // DOCUMENT_H
