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
