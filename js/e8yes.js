
// UIs.
var query_text_box = $("#query_text_box");
var query_submit_button = $("#query_submit_button");
var query_result_area = $("#query_result_area");

var doc_path_text_box = $("#doc_path_text_box");
var doc_path_submit_button = $("#doc_path_submit_button");
var width_progress_bar = $("#width_progress_bar");

// Vars.
var query = "";
var curr_page_num = 0;
var nitem_per_page = 10;

var tunnel_refresh_id;


// Query page.
function post_query() {
        $.ajax({
                url: "/e8yesearch",
                type: "POST",
                data: {
                        query: query,
                        limit: nitem_per_page,
                        page_num: curr_page_num 
                },
                success: function(result) {
                        console.log(result);
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
                query = query_text_box.val();
                post_query();
        }
});

// Query result.

// Tunnel.
function post_tunnel() {
        $.ajax({
                url: "/e8yesearch/Tunnel",
                type: "POST",
                data: {
                        descriptor: doc_path_text_box.val(),
                },
                success: function(result) {
                        console.log(result);
                },
                error: function(xhr, s, e) {
                        console.log(xhr);
                }
        });
}

function track_progress() {
        $.ajax({
                url: "/e8yesearch/Tunnel",
                type: "GET",
                success: function(percent) {
                        width_progress_bar.css("width", (parseFloat(percent)*100) + "%");
                        if (percent >= "1") {
                                clearInterval(tunnel_refresh_id);
                        }
                },
                error: function(xhr, s, e) {
                        console.log(xhr);
                }
        });
}

doc_path_submit_button.on("click", function (e) {
        post_tunnel();
        tunnel_refresh_id = setInterval(track_progress, 200);
});
