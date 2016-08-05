$( function() {
            $( '#draggable' ).draggable();
  } );

window.onload=function(){
    
var kutular = document.createElement('div');
kutular.id = 'draggable';
kutular.className = 'ui-widget-content';
document.getElementsByTagName('body')[0].appendChild(kutular);
    
}