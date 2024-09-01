let P_upload_btn=document.getElementById("P_upload_btn");
let P_upload_btn_label=document.querySelector(".P_upload_btn_label");
let P_load_img=document.querySelector(".P_load_img");
let P_chosen_photo=document.getElementById("P_chosen_photo");
let P_photo_file_name=document.getElementById("P_photo_file_name");
let P_photo_container=document.querySelector(".P_photo_container");

let aim = document.getElementById("P_photo_fname");

//上傳圖片 用 input type=file
P_upload_btn.onchange=() =>{
    let reader= new FileReader();
    reader.readAsDataURL(P_upload_btn.files[0]);
    reader.onload=()=>{
        P_chosen_photo.setAttribute("src",reader.result);
    }
    //.files[0].name 即可取得上傳的檔名
    P_photo_file_name.textContent=P_upload_btn.files[0].name;
    
    P_upload_btn_label.style.display="none";
    P_load_img.style.height='350px';
    P_photo_container.style.width="100%";

    aim.value = P_upload_btn.files[0].name;

}
