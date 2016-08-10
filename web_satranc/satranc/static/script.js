          $( function() {

              $(".whiteMan").draggable({
                  revert: 'invalid',
                  snap: ".black , .white"
              });

              $(".blackMan").draggable({
                  revert: 'invalid',
                  snap: ".black , .white"
              });


              $(".white").droppable();

              $(".black").droppable();

              var startId = false;
              var stopId = false;

              $(".whiteMan, .blackMan").on("dragstart", function(event, ui) {
                startId = $(this).parent().attr("id");
              })

              $(".white, .black").on( "drop", function( event, ui ) {
                stopId = $(this).attr("id");

                if((startId == "1e" && stopId == "1g") || (startId == "8e" && stopId == "8g")){
                  post('', {tasKonum: "kısa rok", oynanacakYer: stopId});
                }else if((startId == "1e" && stopId == "1c") || (startId == "8e" && stopId == "8c")){
                  post('', {tasKonum: "uzun rok", oynanacakYer: stopId});
                }else{
                  post('', {tasKonum: startId, oynanacakYer: stopId});
                }

              } );

          });

          function post(path, params, method) {

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
                error: function(err){
                },
                xhrFields: {
                  withCredentials: true
                }
              });
          }
