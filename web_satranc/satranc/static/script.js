$( function() {

    $(".whiteMan").draggable({
        revert: 'invalid', snap: ".black , .white"
    });

    $(".blackMan").draggable({
        revert: 'invalid', snap: ".black , .white"
    });


    $(".white").droppable();

    $(".black").droppable();

  } );



var dragstartHandler = targetElement.ondragstart;

var man = document.getElementsByClassName(dragstartHandler);
var startId = man[man.length - 1].parentNode.id;

function post(path, params, method) {
    method = method || "post"; // Set method to post by default if not specified.

    // The rest of this code assumes you are not using a library.
    // It can be made less wordy if you use one.
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
}

post('', {tasKonum: startId, oynanacakYer: stopId});
