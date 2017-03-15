#line 1 "pages/result.html"
#include "result.h" 
#line 2 "pages/result.html"
namespace my_skin {
	#line 3 "pages/result.html"
	struct result_documents :public cppcms::base_view
	#line 3 "pages/result.html"
	{
	#line 3 "pages/result.html"
		result::result_documents &content;
	#line 3 "pages/result.html"
		result_documents(std::ostream &_s,result::result_documents &_content): cppcms::base_view(_s),content(_content)
	#line 3 "pages/result.html"
		{
	#line 3 "pages/result.html"
		}
		#line 4 "pages/result.html"
		virtual void render() {
			#line 25 "pages/result.html"
			out()<<"  \n"
				"\n"
				"<html>\n"
				"        <head>\n"
				"                <meta http-equiv=\"Content-Type\" content=\"text/html charset=UTF-8\"/>\n"
				"                <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
				"\n"
				"                <link rel=\"stylesheet\" type=\"text/css\" href=\"../css/theme.css\">\n"
				"\n"
				"                <title>e8yesearch - result</title>\n"
				"        </head>\n"
				"\n"
				"        <body>\n"
				"                <form action=\"/e8yesearch\" method=\"POST\">\n"
				"                        <a href=\"/e8yesearch\">\n"
				"                                <img src=\"../img/logo.png\" />\n"
				"                        </a>\n"
				"                        <input class=\"search-box glowing-border\" name=\"query\" id=\"query_text_box\" type=\"text\" placeholder=\"e8yes\" autofocus>\n"
				"                </form>\n"
				"\n"
				"                <div class=\"form-result\">\n"
				"                        <h4>Your query is: ";
			#line 25 "pages/result.html"
			out() << content.query; 
			#line 26 "pages/result.html"
			out()<<".</h4>\n"
				"                        <h4>";
			#line 26 "pages/result.html"
			out() << content.docs.size(); 
			#line 27 "pages/result.html"
			out()<<" documents retrieved.</h4>\n"
				"                        ";
			#line 27 "pages/result.html"
			for (unsigned i = 0; i < 10; i ++) { 
			#line 29 "pages/result.html"
			out()<<"\n"
				"                                <div class=\"result-cell\">\n"
				"                                        ";
			#line 29 "pages/result.html"
			const std::string& heading = content.docs[i].get_heading(); 
			#line 30 "pages/result.html"
			out()<<"\n"
				"                                        ";
			#line 30 "pages/result.html"
			const std::string& url = content.docs[i].get_url(); 
			#line 32 "pages/result.html"
			out()<<"\n"
				"\n"
				"                                        <h3 class=\"search-heading\">";
			#line 32 "pages/result.html"
			out() << heading; 
			#line 33 "pages/result.html"
			out()<<"</h3>\n"
				"                                        <a class=\"search-link\" href=\"";
			#line 33 "pages/result.html"
			out() << url; 
			#line 33 "pages/result.html"
			out()<<"\">";
			#line 33 "pages/result.html"
			out() << url; 
			#line 36 "pages/result.html"
			out()<<"</a>\n"
				"                                        <div class=\"result-snippet\">No description.</div>\n"
				"                                </div>\n"
				"                        ";
			#line 36 "pages/result.html"
			} 
			#line 45 "pages/result.html"
			out()<<"\n"
				"                </div>\n"
				"\n"
				"                <script type=\"text/script\" src=\"../js/jquery.js\"></script>\n"
				"                <script type=\"text/script\" src=\"../js/jquery-ui.js\"></script>\n"
				"                <script type=\"text/script\" src=\"../js/e8yes.js\"></script>\n"
				"        </body>\n"
				"</html>\n"
				"\n"
				"";
		#line 45 "pages/result.html"
		} // end of template render
	#line 46 "pages/result.html"
	}; // end of class result_documents
#line 47 "pages/result.html"
} // end of namespace my_skin
#line 48 "pages/result.html"
namespace {
#line 48 "pages/result.html"
 cppcms::views::generator my_generator; 
#line 48 "pages/result.html"
 struct loader { 
#line 48 "pages/result.html"
  loader() { 
#line 48 "pages/result.html"
   my_generator.name("my_skin");
#line 48 "pages/result.html"
   my_generator.add_view<my_skin::result_documents,result::result_documents>("result_documents",true);
#line 48 "pages/result.html"
    cppcms::views::pool::instance().add(my_generator);
#line 48 "pages/result.html"
 }
#line 48 "pages/result.html"
 ~loader() {  cppcms::views::pool::instance().remove(my_generator); }
#line 48 "pages/result.html"
} a_loader;
#line 48 "pages/result.html"
} // anon 
