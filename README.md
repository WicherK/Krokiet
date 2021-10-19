# Krokiet

*__Krokiet__* - really basic keylogger written in C++.

## Short Explanation

* Program is reading strokes and every stroke is added to vector called *strokesPackage*.
* Program is checking if *strokesPackage* length is greater than 100 or equals 100.
* If the condition is met, we are going to save strokes to the file and then send it via mail.
* To send message, application is using curl command when message is sent, file will be deleted.

## Usage

Before run make sure you changed this parameters:

- *path* - variable that contains path to file with strokes (optional). 
- [SMTP_SERVER] - smtp server like smtp.gmail.com:465.
- [EMAIL] - your email.
- [PASSWORD] - password to your mail.
- [EMAIL_RECEIVER] - mail that is going to receive a message.

Compile and run the compiled *.exe* file. Program is going to be in hidden mode and will send a message every 100 strokes to your mail.

## Future features

* Hide process of Krokiet in task manager.
* Message is sent before computer shutdown not every 100 strokes.

## License
[MIT](https://choosealicense.com/licenses/mit/)
