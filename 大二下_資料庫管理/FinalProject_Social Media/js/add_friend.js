function all(){

    $.ajax({
        type :"GET",
        url :'/php/add_friend.php',
        success:function(response){
            response = JSON.parse(response);

            var add_friend = "";

            if(response.length){             
                $.each(response,function(key,value){
                    add_friend +='<div class = "row" id="add'+value.user_no+'">';
                    add_friend += '<a href="#" class="row-item row-item-action">';
                    add_friend += '<div class = "col-3 str_face">';
                    add_friend += "<img src='"+value.user_photo+"' style='width:70px; height:70px;'></img>";
                    add_friend += '</div>';
                    add_friend += '<div class = "col-4 str_name">'+value.nickname+'</div>';
                    add_friend += '<div class = "col-5 str_bu">';
                    add_friend += "<button type='button' class='btn btn-secondary follow_bu' data-id='"+value.user_no+"' onClick = 'addClickID(this.id)'>Follow</button>";
                    add_friend += '</div>';
                    add_friend +='</div>';
                });
              
            }
            $(".row-5 str").html(add_friend);
        }
    });
}
//<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
//<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">