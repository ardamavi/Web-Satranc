          $( function() {
              make_draggable();
              make_droppable();
              bind_events();
          });

          function post(path, params, method) {
            lock_board();
            params.csrfmiddlewaretoken = $("input[name='csrfmiddlewaretoken']").val();
              $.ajax({
                url: path,
                method: 'POST',
                data: params,
                success: function(data){
                  var $body = $("body");
                  $body.children(".chessboard").remove();
                  $body.prepend(data);
                },
                error: function(){
                },
                xhrFields: {
                  withCredentials: true
                }
              });
          }

          function make_draggable() {
            var order = $("#order").html() === "white" ? ".whiteMan" : ".blackMan";
            $(order).draggable({
              revert: "invalid",
              snap: ".black, .white"
            });
          }

          function make_droppable() {
            $(".white").droppable();
            $(".black").droppable();
          }

          function lock_board() {
            var order = $("#order").html() === "white" ? ".whiteMan" : ".blackMan";
            $(order).draggable( "option", "disabled", true );
            $(".white, .black").droppable( "option", "disabled", true );
          }

          function bind_events() {
            var startId = false;
            var stopId = false;
            $(".whiteMan, .blackMan").on("dragstart", function(event, ui) {
              startId = $(this).parent().attr("id");
            })

            $(".white, .black").on( "drop", function( event, ui ) {
              stopId = $(this).attr("id");

              if((startId == "1e" && stopId == "1g") || (startId == "8e" && stopId == "8g")){
                post('', {tasKonum: "kısa rok", oynanacakYer: stopId, order: $("#order").html()});
              }else if((startId == "1e" && stopId == "1c") || (startId == "8e" && stopId == "8c")){
                post('', {tasKonum: "uzun rok", oynanacakYer: stopId, order: $("#order").html()});
              }else{
                post('', {tasKonum: startId, oynanacakYer: stopId, order: $("#order").html()});
              }

            } );
          }
