#ifdef __cplusplus
extern "C" {
#endif

#ifndef CTYPE_H
#define CTYPE_H

int isalnum(int c); // digit+alpha
int isalpha(int c); // lower+upper
int iscntrl(int c); // 0-31 + 127
int isdigit(int c); // {0,1,2,3,4,5,6,7,8,9}
int isgraph(int c); // alpha+punct
int islower(int c); // {a b c d e f g h i j k l m n o p q r s t u v w x y z}
int isprint(int c); // alnum+punct+space
int ispunct(int c); // {! " # $ % & ' () * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~}
int isspace(int c); // {\t \n \r \c space}
int isupper(int c); // {A B C D E F G H I J K L M N O P Q R S T U V W X Y Z}
int isxdigit(int c); // {0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F}

int tolower(int c);
int toupper(int c);

#endif

#ifdef __cplusplus
}
#endif
