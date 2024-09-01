/* get basket items from JSON */
var fr_row=document.querySelector(".fr");
var str_row=document.querySelector(".str");
var my_name=document.querySelector(".my_name");
var my_face=document.querySelector(".my_faceImg");
var post_col=document.querySelector(".post_col");
var post_face=document.querySelector(".post_face img");
var post_name=document.querySelector(".post_name");
var post_time=document.querySelector(".post_time span");
var post_text=document.querySelector(".post_text");
var post_pic=document.querySelector(".post_pic img");
var trytry=document.createElement("div");

let getResponse=async(url) => {
    let result = await fetch(url);
    let data = await result.json();

    let myinfo = data.friend.me;
    my_name.textContent = myinfo.nickname;
    my_face.setAttribute("src", "img/HeadPhoto/"+myinfo.user_photo);
    
    let friendItems = data.friend.fr;

    friendItems = friendItems.map(item => {
        let fr_no = item.user_no;
        let fr_photo = item.user_photo;
        let fr_name = item.nickname;
        return {fr_no, fr_photo, fr_name};
    })

    friendItems.forEach((item) => {
        var new_fr_info = document.createElement("div");
        new_fr_info.setAttribute("class", "row fr_info");
        var new_fr_face = document.createElement("div");
        new_fr_face.setAttribute("class", "col-3 fr_face");
        var new_fr_faceImg = document.createElement("img");
        new_fr_faceImg.setAttribute("src", "img/HeadPhoto/"+item.fr_photo);
        new_fr_faceImg.setAttribute("class", "fr_faceImg")
        var new_fr_name = document.createElement("div");
        new_fr_name.setAttribute("class", "col-4 fr_name");
        new_fr_name.textContent = item.fr_name;
        var new_fr_bu = document.createElement("div");
        new_fr_bu.setAttribute("class", "col-5 fr_bu");
        var new_fr_form = document.createElement("form");
        new_fr_form.setAttribute("class", "fr_form");
        new_fr_form.setAttribute("method", "get");
        new_fr_form.setAttribute("action", "php/delete_friend_result.php");
        var fr_form_input = document.createElement("input");
        fr_form_input.setAttribute("type", "hidden");
        fr_form_input.setAttribute("name", "delete_friend_no");
        fr_form_input.setAttribute("id", "fr_no:"+item.fr_no);
        fr_form_input.setAttribute("value", item.fr_no);
        var new_unfollow_bu = document.createElement("button");
        new_unfollow_bu.setAttribute("type", "submit");
        new_unfollow_bu.setAttribute("class", "btn btn-secondary unfollow_bu");
        new_unfollow_bu.textContent = "Unfollow";

        fr_row.appendChild(new_fr_info);
        new_fr_info.appendChild(new_fr_face);
        new_fr_face.appendChild(new_fr_faceImg);
        new_fr_info.appendChild(new_fr_name);
        new_fr_info.appendChild(new_fr_bu);
        new_fr_bu.appendChild(new_fr_form);
        new_fr_form.appendChild(fr_form_input);
        new_fr_form.appendChild(new_unfollow_bu);
    })

    let suggestItems = data.friend.str;

    suggestItems = suggestItems.map(item => {
        let str_no = item.user_no;
        let str_photo = item.user_photo;
        let str_name = item.nickname;
        return {str_no, str_photo, str_name};
    })

    suggestItems.forEach((item)=> {
        var new_str_info = document.createElement("div");
        new_str_info.setAttribute("class", "row str_info");
        var new_str_face = document.createElement("div");
        new_str_face.setAttribute("class", "col-3 str_face");
        var new_str_faceImg = document.createElement("img");
        new_str_faceImg.setAttribute("class", "str_faceImg");
        new_str_faceImg.setAttribute("src", "img/HeadPhoto/"+item.str_photo);
        var new_str_name = document.createElement("div");
        new_str_name.setAttribute("class", "col-4 str_name");
        new_str_name.textContent = item.str_name;
        var new_str_bu = document.createElement("div");
        new_str_bu.setAttribute("class", "col-5 str_bu");
        var new_str_form = document.createElement("form");
        new_str_form.setAttribute("class", "str_form");
        new_str_form.setAttribute("method", "get");
        new_str_form.setAttribute("action", "php/add_friend_result.php");
        var str_form_input = document.createElement("input");
        str_form_input.setAttribute("type", "hidden");
        str_form_input.setAttribute("name", "add_friend_no");
        str_form_input.setAttribute("id", "str_no:"+item.str_no);
        str_form_input.setAttribute("value", item.str_no);
        var new_follow_bu = document.createElement("button");
        new_follow_bu.setAttribute("type", "submit");
        new_follow_bu.setAttribute("class", "btn btn-secondary follow_bu");
        new_follow_bu.textContent = "Follow";

        str_row.appendChild(new_str_info);
        new_str_info.appendChild(new_str_face);
        new_str_face.appendChild(new_str_faceImg);
        new_str_info.appendChild(new_str_name);
        new_str_info.appendChild(new_str_bu);
        new_str_bu.appendChild(new_str_form);
        new_str_form.appendChild(str_form_input);
        new_str_form.appendChild(new_follow_bu);
    })

    let postItems = data.post;
    postItems = postItems.map(item =>{
        let user_photo = item.user_photo;
        let nickname = item.nickname;
        let time = item.time;
        let content = item.content;
        let picture = item.picture;
        return {user_photo, nickname, time, content, picture};
    })

    postItems.forEach((item)=>{

        var new_post=document.createElement("div");
        new_post.setAttribute("class", "post color2");

        var new_row=document.createElement("div");
        new_row.setAttribute("class", "row m_square");

        var new_post_face=document.createElement("div");
        new_post_face.setAttribute("class", "col-3  post_face");

        var new_post_faceImg=document.createElement("img");
        new_post_faceImg.setAttribute("src", "img/HeadPhoto/"+item.user_photo);


        var new_post_info=document.createElement("div");
        new_post_info.setAttribute("class", "col-9 post_info");

        var new_post_name=document.createElement("div");
        new_post_name.setAttribute("class", "post_name color4");
        new_post_name.textContent=item.nickname;
            
        var new_post_time=document.createElement("div");
        new_post_time.setAttribute("class", "post_time");
            
        var new_post_time_text=document.createElement("span");
        new_post_time_text.setAttribute("class", "post_time_text");
        new_post_time_text.textContent=item.time;

        var new_post_content=document.createElement("div");
        new_post_content.setAttribute("class", "post_content")

        var new_post_text=document.createElement("div");
        new_post_text.setAttribute("class", "post_text color3");
        new_post_text.textContent = item.content;

        var new_post_pic=document.createElement("div");
        new_post_pic.setAttribute("class", "post_pic");
        var new_post_picImg=document.createElement("img");
        new_post_picImg.setAttribute("src", 'img/PostImg/'+item.picture);

        post_col.appendChild(new_post); 
        new_post.appendChild(new_row);
        new_row.appendChild(new_post_face);
        new_post_face.appendChild(new_post_faceImg);
        new_row.appendChild(new_post_info);
        new_post_info.appendChild(new_post_name);
        new_post_info.appendChild(new_post_time);
        new_post_time.appendChild(new_post_time_text);
        new_row.appendChild(new_post_content);
        new_post_content.appendChild(new_post_text);
        new_post_content.appendChild(new_post_pic);
        new_post_pic.appendChild(new_post_picImg);
    })    
            
}

document.addEventListener("DOMContentLoaded", ()=>{
    const home=getResponse('php/Home.php');
})