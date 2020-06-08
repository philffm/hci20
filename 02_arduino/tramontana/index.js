<!-- import jquery -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
<!-- import p5js -->
<script src="https://cdnjs.cloudflare.com/ajax/libs/p5.js/0.5.4/p5.min.js"></script>
<!-- import tramontana -->
<script src="lib/tramontana_min.js"></script>


 
var device = new tramontana();  

function setup(){ 				
    createCanvas(600, 600); 				
    device.start("192.168.1.23",  function(e){
    if(e==undefined){
    //SUCCESS TRAMONTANA CONNECTED
    device.makeVibrate();
    }
    });
    
    function draw()
    {
    rect(10,10,100,100);
    }
    
}
    