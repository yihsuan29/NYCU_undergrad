let post= document.querySelectorAll('.post');
var seepost=document.querySelector('.see_post');
var exit=document.querySelector('.exit_btn');

//從原畫面可以點開每個小貼文
post.forEach(p => {
    p.addEventListener('click',  function() {
        seepost.style.display = "block";
    });
});
exit.addEventListener('click',  function() {
    seepost.style.display = "none";
});