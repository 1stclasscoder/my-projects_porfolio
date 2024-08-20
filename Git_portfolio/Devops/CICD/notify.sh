if [[ $CI_JOB_STATUS == 'success' ]]; then
    CI_JOB_STATUS="SUCCESS"
else
    CI_JOB_STATUS="FAIL"
fi
token_bota="7050364026:AAG1cXkRltQbuytLRpA700r0QdRKMyTXPXk"
id_telega="655823427"
url="https://api.telegram.org/bot${token_bota}/sendMessage"
TEXT="Author: $CI_COMMIT_AUTHOR Job name: $CI_JOB_NAME Status: $CI_JOB_STATUS Project: $CI_PROJECT_NAME"
curl -s -d "chat_id=$id_telega&disable_web_page_preview=1&text=$TEXT" $url > /dev/null