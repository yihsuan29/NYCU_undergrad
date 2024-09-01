let S_upload_btn=document.getElementById("S_upload_btn");
let S_upload_btn_label=document.querySelector(".S_upload_btn_label");
let S_load_img=document.querySelector(".S_load_img");
let S_chosen_photo=document.getElementById("S_chosen_photo");
let S_photo_file_name=document.getElementById("S_photo_file_name");
let S_photo_container=document.querySelector(".S_photo_container");;

let S_photo_name = document.getElementById('S_photo_name'); //edit
//上傳圖片 用 input type=file
S_upload_btn.onchange=() =>{
    let reader= new FileReader();
    reader.readAsDataURL(S_upload_btn.files[0]);
    reader.onload=()=>{
        S_chosen_photo.setAttribute("src",reader.result);
    }
    //.files[0].name 即可取得上傳的檔名
    S_photo_file_name.textContent=S_upload_btn.files[0].name;
    S_load_img.style.height='300px';
    S_photo_container.style.width="100%";
    S_exit_btn.style.marginTop="10px";

    S_photo_name.value = S_upload_btn.files[0].name; //edit 
}