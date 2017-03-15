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
				"                <a href=\"/e8yesearch\">\n"
				"                        <img src=\"../img/logo.png\" />\n"
				"                </a>\n"
				"                <input class=\"input\" id=\"query_text_box\" type=\"text\" placeholder=\"e8yes\">\n"
				"\n"
				"                <div class=\"form-result\" id=\"query_result_area\"></div>\n"
				"\n"
				"                <script type=\"text/javascript\">\n"
				"                        var result_documents = JSON.parse(\"";
			#line 25 "pages/result.html"
			out()<<cppcms::filters::raw(content.json_docs);
			#line 34 "pages/result.html"
			out()<<"\");\n"
				"                </script>\n"
				"\n"
				"                <script type=\"text/script\" src=\"../js/jquery.js\"></script>\n"
				"                <script type=\"text/script\" src=\"../js/jquery-ui.js\"></script>\n"
				"                <script type=\"text/script\" src=\"../js/e8yes.js\"></script>\n"
				"        </body>\n"
				"</html>\n"
				"\n"
				"";
		#line 34 "pages/result.html"
		} // end of template render
	#line 35 "pages/result.html"
	}; // end of class result_documents
#line 36 "pages/result.html"
} // end of namespace my_skin
#line 37 "pages/result.html"
namespace {
#line 37 "pages/result.html"
 cppcms::views::generator my_generator; 
#line 37 "pages/result.html"
 struct loader { 
#line 37 "pages/result.html"
  loader() { 
#line 37 "pages/result.html"
   my_generator.name("my_skin");
#line 37 "pages/result.html"
   my_generator.add_view<my_skin::result_documents,result::result_documents>("result_documents",true);
#line 37 "pages/result.html"
    cppcms::views::pool::instance().add(my_generator);
#line 37 "pages/result.html"
 }
#line 37 "pages/result.html"
 ~loader() {  cppcms::views::pool::instance().remove(my_generator); }
#line 37 "pages/result.html"
} a_loader;
#line 37 "pages/result.html"
} // anon 
