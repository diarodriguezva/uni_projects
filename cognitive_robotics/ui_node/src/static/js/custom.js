
(function($){

        var x = 0.0;
        var y = 0.0;
        var z = 0.0;
        
        // Fetch gripper's coordinates and set them to val
        $('#refresh-coordinates').trigger("click");

    function contains(s, subs) {
        if (s.indexOf(subs) > -1) {
            return true;
        }
        return false;
    }

    $('#submit-xml').click(function() {

        xml = $('#textarea-xml').val();
        console.log(xml);

        $.ajax({
            url: '/input-xml',
            type: 'POST',
            data: {"xml" : xml},
            dataType:"json",
            success: function (result) {
                console.log(result.data);
            }
        });
    });

    $('.gripper-grasp').click(function() {

        cmd = $(this).attr('id')
        console.log(cmd);

        $.ajax({
            url: '/gripper-grasp',
            type: 'POST',
            data: {"cmd" : cmd},
            dataType:"json",
            success: function (result) {
                console.log(result.data);
            }
        });
    });

    $('.gripper-move').click(function() {

        color = $(this).attr('id')
        console.log(color);

        $.ajax({
            url: '/gripper-move',
            type: 'POST',
            data: {"cmd" : color},
            dataType:"json",
            success: function (result) {
                console.log(result.data);
            }
        });
    });

    $('#gripper-coordinates').click(function() {

        coord = $("#gripper-coordinates-input").val();
        console.log(coord);

        $.ajax({
            url: '/gripper-coordinates',
            type: 'POST',
            data: {"cmd" : coord},
            dataType:"json",
            success: function (result) {
                console.log(result.data);
            }
        });
    });
    
     $('#refresh-coordinates').click(function() {

            $.ajax({
                url: "/gripper-pose",
                type: "GET",
                success: function(data) {
                
                    var d = data["data"].map(function(num) {
                        return num.toFixed(3);
                    })
                    
                    console.log(data["data"]);
                    
                    if (data["data"].length) {
                        x = parseFloat(d[0]);
                        y = parseFloat(d[1]);
                        z = parseFloat(d[2]);
                    }
                    
                    d = d.join(' ');
                    
                    $("#gripper-coordinates-input").val(d);
                },
                dataType: "json",
                timeout: 500
            })

    });
    
    (function poll() {
        setTimeout(function() {
            // GET-OBJECTS
            $.ajax({
                url: "/get-objects",
                type: "GET",
                success: function(data) {
                    $("#objects-field").empty();
                    $.each(data, function(key, value) {
                        if (value["status"] == "error") {
                            var str = "<li class='list-group-item list-group-item-danger'>\
                                      Could not connect to service</li>";
                        }
                        else if (value) {                            
                            var str = "\
                            <a href='#' class='list-group-item'>\
                            <h5 class='list-group-item-heading'>" + value["color"] + "</h5>\
                            <p class='list-group-item-text'><small>X: " + value["location"][0] + "<br>Y: "
                            + value["location"][1] + "<br>Z: " + value["location"][2] + "</small><br></p>\
                            </a>\
                            " 
                        }
                        $("#objects-field").append(str);
                    });
                    if (data.length === 0) {
                    var str = "<li class='list-group-item list-group-item-info'>\
                                No objects found.</li>";
                    $("#objects-field").append(str);
                    }
                },
                dataType: "json",
                complete: poll,
                timeout: 5000
            })

        }, 2000);
    })();

    (function poll2() {
        setTimeout(function() {
            // ROSOUT
            
            $.ajax({
                url: "/rosout",
                type: "GET",
                success: function(data) {
                
                    var items = $("#rosout-items");
                    var d = data["data"];
                    var color = "";
                    
                    if (d) {
                        // for different log levels
                        if (contains(d, "[ERROR]") || contains(d, "[FATAL]")) {
                            color = "text-danger";
                        }
                        else if (contains(d, "[INFO]")) {
                            color = "text-info";
                        }
                        else if (contains(d, "[DEBUG]")) {
                            color = "text-muted";
                        }
                        else if (contains(d, "[WARN]")) {
                            color = "text-warning";
                        }
                        var str = "<p class='" + color + "'>" + d + "</p>";
                        items.prepend(str);
                        
                    }
                    while (items.children().size() >= 50) {
                        items.children().last().remove();
                    }
                    
                },
                dataType: "json",
                complete: poll2,
                timeout: 2500
            })
        }, 500);
    })();
    
    // Keypresses for QA, WS, ED
    // Quick control for robot
    $(function() {
       $(window).keypress(function(e) {
       
           if ($("#enable-input").hasClass('active')) { // if enable-input button is pressed
               var key = e.which;
               
               // Q and A
               if (key==113) {
                 x += 0.025;
               }
               else if (key==97) {
                 x -= 0.025;
               }
               
               // W and S
               else if (key==119) {
                 y += 0.025;
               }
               else if (key==115) {
                 y -= 0.025;
               }
               
               // E and D
               else if (key==101) {
                 z += 0.025;
               }
               else if (key==100) {
                 z -= 0.025;
               }
               
               $("#gripper-coordinates-input").val(x.toFixed(3) + " " + y.toFixed(3) + " " + z.toFixed(3));
               
               $('#gripper-coordinates').trigger("click");
           }

       });
    });

    $('#gripper-coordinates').tooltip({
            placement: "bottom",
            trigger: "focus",
            delay: 250
        });
    
    
    // Placeholder text for xml input box
    var prexml = "\
<instructions>\n\
    <move>\n\
        <obj>\n\
            <type shape='sphere' color='green'/>\n\
        </obj>\n\
        <tolocation>\n\
            <type shape='bin' color='green'/>\n\
        </tolocation>\n\
    </move>\n\
</instructions>";

    $('#textarea-xml').val(prexml);


})(window.jQuery);
