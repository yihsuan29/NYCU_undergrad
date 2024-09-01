let pop_edit_btn = document.querySelector(".pop_edit_btn");
let pop_post_text_container = document.querySelector(".pop_post_text_container");
let pop_post_edit_container = document.querySelector(".pop_post_edit_container");
let edit_post_btn = document.querySelector(".edit_post_btn");
let edit_post_text = document.querySelector(".edit_post_text");
let edit_post_num = document.getElementById("edit_post_num");
let del_post_num = document.getElementById("del_post_num");

pop_edit_btn.addEventListener('click',  function() {
    pop_post_text_container.style.display = "none";
    pop_post_edit_container.style.display = "flex";
    pop_edit_btn.style.display= "none";
    //edit_post_text.placeholder=post_content.textContent;
    edit_post_text.value=post_content.textContent;
    edit_post_num.value = post_num.textContent;
    del_post_num.value = post_num.textContent;
});
edit_post_btn.addEventListener('click',  function() {
    pop_post_text_container.style.display = "flex";
    pop_post_edit_container.style.display = "none";
    pop_edit_btn.style.display= "flex";
});