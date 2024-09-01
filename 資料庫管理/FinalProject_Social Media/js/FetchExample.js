// Fetch API
let getResponse = async(url) => {
    let response = await fetch(url);
    return response.json();
}

// For Home.php, user_no=1
const home = await getResponse('http://127.0.0.1/FinalProject/php/Home.php?user_no=1');
// Post
const post_face = home.post[0].user_photo;
const post_name = home.post[0].nickname;
const post_time = home.post[0].time;
const post_text = home.post[0].content;
const post_pic = home.post[0].picture;
// Friend
const my_face = home.friend.me.user_photo;
const my_name = home.friend.me.nickname;
const fr_face = home.friend.fr[0].user_photo;
const fr_name = home.friend.fr[0].nickname;
const str_face = home.friend.str[0].user_photo;
const str_name = home.friend.str[0].nickname;

// For PersonalHome.php, user_no=1, post_no=1
const personal = await getResponse('http://127.0.0.1/FinalProject/php/PersonalHome.php?user_no=1');
const pop = await getResponse('http://127.0.0.1/FinalProject/php/PersonalHome.php?post_no=1');
// Info
const user_photo = personal.info.user_photo;
const user_name = personal.info.nickname;
const other_info = personal.info.bio;
// Content
const post_num = personal.content[0].post_no;
const post_photo = personal.content[0].picture;
// Pop Post
const pop_post_photo = post_photo; // Same as above
const pop_user_photo = user_photo; // Same as above
const pop_user_name = user_name; // Same as above
const pop_post_num = post_num; // Same as above
const pop_post_text = pop.content;
const pop_post_time = pop.time; // Not included in frontend design diagram