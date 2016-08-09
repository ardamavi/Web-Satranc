/*$( function() {

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

    startId = "";

    $(".whiteMan").on("dragstart", function(event, ui) {
      startId = $(this).parent().attr("id");
    })

    $(".blackMan").on("dragstart", function(event, ui) {
      startId = $(this).parent().attr("id");
    })

    $( ".white" ).on( "drop", function( event, ui ) {
      stopId = $(this).attr("id");
      post('', {tasKonum: startId, oynanacakYer: stopId});
    } );

    $( ".black" ).on( "drop", function( event, ui ) {
      stopId = $(this).attr("id");
      post('', {tasKonum: startId, oynanacakYer: stopId});
    } );

});

function post(path, params, method) {
    method = method || "post";

    var form = document.createElement("form");
    {% csrf_token %}
    form.setAttribute("method", method);
    form.setAttribute("action", path);

    for(var key in params) {
        if(params.hasOwnProperty(key)) {
            var hiddenField = document.createElement("input");
            hiddenField.setAttribute("type", "hidden");
            hiddenField.setAttribute("name", key);
            hiddenField.setAttribute("value", params[key]);

            form.appendChild(hiddenField);
         }
    }

    document.body.appendChild(form);
    form.submit();
}*/
