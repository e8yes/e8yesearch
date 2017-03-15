
// UIs.
var query_text_box = $("#query_text_box");
var query_submit_button = $("#query_submit_button");
var query_result_area = ("#query_result_area");

// Vars.
var query = "";
var curr_page_num = 0;
var nitem_per_page = 10;


// Funcs.
function display_result(result) {
}

function post_query() {
        $.ajax({
                url: "/e8yesearch",
                type: "POST",
                data: {
                        query: query,
                        limit: nitem_per_page,
                        page_num: curr_page_num 
                },
                success: function(e) {
                        console.log(e);
                },
                error: function(xhr, s, e) {
                        console.log(xhr);
                }
        });
}

query_submit_button.on("click", function (e) {
        query = query_text_box.val();
        post_query();
});

query_text_box.on("keypress", function (e) {
        if (e.keyCode === 13) {
                // Enter key pressed.
                query = query_text_box.val() + String.fromCharCode(e.keyCode);
                post_query();
        }
});
