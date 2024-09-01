let post= document.querySelectorAll('.post');
var seepost=document.querySelector('.see_post');
var exit=document.querySelector('.exit_btn');
var post_photo=document.querySelector('.pop_post_photo');
var post_num=document.querySelector('.pop_post_num');
var post_content=document.querySelector('.pop_post_text');

//從原畫面可以點開每個小貼文
post.forEach(p => {
    p.addEventListener('click',  function() {
        let post_num_here=this.querySelector(".post_num");
        var number=post_num_here.textContent;
        var post_content_text=this.querySelector(".post_content_text");
        seepost.style.display = "block";
        post_num.textContent=String(number);
        post_content.textContent=String(post_content_text.textContent);
        var source="img/PostImg/"+String(number)+".jpg"; //之後應該是要從query選到圖片名稱
        post_photo.src=source;
    });
});
exit.addEventListener('click',  function() {
    pop_post_text_container.style.display = "flex";
    pop_post_edit_container.style.display = "none";
    pop_edit_btn.style.display= "flex";
    seepost.style.display = "none";
});


