function all(){

    $.ajax({
        type :"GET",
        url :'/php/delete_friend.php',
        success:function(response){
            response = JSON.parse(response);

            var delete_friend = "";

            if(response.length){

                $.each(response,function(key,value){
                    delete_friend += '<a href="#" class="row fr_info-item row fr_info-item-action">';
                    delete_friend +='<div class = "row fr_info" id="delete'+value.user_no+'">';
                    delete_friend += '<div class = "col-3 fr_face">';
                    delete_friend +=  "<img src='"+value.user_photo+"' style='width:70px; height:70px;'></img>";
                    delete_friend += '</div>';
                    delete_friend += '<div class = "col-4 fr_name">'+value.nickname+'</div>';
                    delete_friend += '<div class = "col-5 fr_bu">';
                    delete_friend += "<button type='button' class='btn btn-secondary unfollow_bu' id='"+value.user_no+"' onClick = 'deleteClickID(this.id)' >Unfollow</button>";
                    delete_friend += '</div>';
                    delete_friend +='</div>';
                });
                
            }
            $(".row-5 fr").html(delete_friend);
        }
    });
}