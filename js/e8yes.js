var query_text_box = $("#query_text_box");
var query_submit_button = $("#query_submit_button");

function display_result(e) {
}

query_submit_button.on("click", function (e) {
        $.ajax({
                url: "/e8yes",
                type: "GET",
                data: {
                        query: query_text_box.val(),
                },
                success: function(e) {
                        console.log(e);
                        display_result(e);
                },
                error: function(xhr, s, e) {
                        console.log("error");
                }
        });
});
