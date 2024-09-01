let R_upload_btn=document.getElementById("R_upload_btn");
let R_upload_btn_label=document.querySelector(".R_upload_btn_label");
let R_load_img=document.querySelector(".R_load_img");
let R_chosen_photo=document.getElementById("R_chosen_photo");
let R_photo_file_name=document.getElementById("R_photo_file_name");
let R_photo_container=document.querySelector(".R_photo_container");

let R_photo_name = document.getElementById("R_photo_name");

//上傳圖片 用 input type=file
R_upload_btn.onchange=() =>{
    let reader= new FileReader();
    reader.readAsDataURL(R_upload_btn.files[0]);
    reader.onload=()=>{
        R_chosen_photo.setAttribute("src",reader.result);
    }
    //.files[0].name 即可取得上傳的檔名
    R_photo_file_name.textContent=R_upload_btn.files[0].name;
    R_upload_btn_label.style.display="none";
    R_load_img.style.height='300px';
    R_photo_container.style.width="100%";

    R_photo_name.value = R_upload_btn.files[0].name;

}