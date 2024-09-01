function addClickID(clickid){
    var add_user_id = clickid;
    var add_id = 'add'+add_user_id;
    var add_fr = document.getElementById(add_id);
    add_fr.remove();
    window.location.href='/php/add_friend_result.php?add_friend_no=' + add_user_id;
    
}