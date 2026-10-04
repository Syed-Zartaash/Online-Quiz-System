#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to convert URL encoding (like %20 or +) to normal text
void decode_url(char *src, char *dest) {
    while (*src) {
        if (*src == '+') {
            *dest = ' ';
        } else if (*src == '%' && isxdigit(src[1]) && isxdigit(src[2])) {
            char hex[3] = { src[1], src[2], '\0' };
            *dest = (char)strtol(hex, NULL, 16);
            src += 2;
        } else {
            *dest = *src;
        }
        src++;
        dest++;
    }
    *dest = '\0';
}

void get_value(char *data, char *key, char *output) {
    char temp[100] = "";
    char *pos = strstr(data, key);
    if (pos) {
        pos += strlen(key) + 1;
        int i = 0;
        while (pos[i] != '&' && pos[i] != '\0') {
            temp[i] = pos[i];
            i++;
        }
        temp[i] = '\0';
        decode_url(temp, output);
    }
}

int main() {
    printf("Content-Type: text/html\n\n");

    char *data = getenv("QUERY_STRING");
    char name[100] = "Student", q_str[5] = "0", score_str[5] = "0", ans[5] = "";
    
    if (data) {
        get_value(data, "name", name);
        get_value(data, "q", q_str);
        get_value(data, "score", score_str);
        get_value(data, "ans", ans);
    }

    int q = atoi(q_str);
    int score = atoi(score_str);

    // Scoring Logic
    if (q == 2) { 
        if (strcmp(ans, "c") == 0) score++; // Q1: 1947
    } else if (q == 3) {
        if (strcmp(ans, "a") == 0) score++; // Q2: Islamabad
    } else if (q == 4) {
        if (strcmp(ans, "a") == 0) score++; // Q3: Allama Iqbal
    } else if (q == 5) {
        if (strcmp(ans, "b") == 0) score++; // Q4: K2
    } else if (q == 6) {
        if (strcmp(ans, "a") == 0) score++; // Q5: Urdu
    }

    // Header with CSS link
    printf("<html><head><link rel='stylesheet' type='text/css' href='../style.css'></head><body>");
    
    // UPDATED: Using 'box' class to match your CSS file
    printf("<div class='box'>");

    if (q <= 5) {
        printf("<h2>Pakistan Studies Quiz</h2>");
        printf("<p style='text-align:center;'>Student: <b>%s</b> | Current Score: %d</p><hr>", name, score);
        printf("<form action='quiz.exe' method='GET' style='text-align:left; padding-left:10px;'>");
        
        if (q == 1) {
            printf("<p><b>1. When did Pakistan gain independence?</b></p>");
            printf("<input type='radio' name='ans' value='a' required> 1940<br>");
            printf("<input type='radio' name='ans' value='b'> 1945<br>");
            printf("<input type='radio' name='ans' value='c'> 1947<br>");
        } else if (q == 2) {
            printf("<p><b>2. What is the capital of Pakistan?</b></p>");
            printf("<input type='radio' name='ans' value='a' required> Islamabad<br>");
            printf("<input type='radio' name='ans' value='b'> Karachi<br>");
            printf("<input type='radio' name='ans' value='c'> Lahore<br>");
        } else if (q == 3) {
            printf("<p><b>3. Who is the national poet of Pakistan?</b></p>");
            printf("<input type='radio' name='ans' value='a' required> Allama Iqbal<br>");
            printf("<input type='radio' name='ans' value='b'> Faiz Ahmed Faiz<br>");
            printf("<input type='radio' name='ans' value='c'> Ahmad Faraz<br>");
        } else if (q == 4) {
            printf("<p><b>4. Which is the highest peak in Pakistan?</b></p>");
            printf("<input type='radio' name='ans' value='a' required> Nanga Parbat<br>");
            printf("<input type='radio' name='ans' value='b'> K2<br>");
            printf("<input type='radio' name='ans' value='d'> Mount Everest<br>");
        } else if (q == 5) {
            printf("<p><b>5. What is the national language of Pakistan?</b></p>");
            printf("<input type='radio' name='ans' value='a' required> Urdu<br>");
            printf("<input type='radio' name='ans' value='b'> Punjabi<br>");
            printf("<input type='radio' name='ans' value='c'> Sindhi<br>");
        }

        printf("<input type='hidden' name='name' value='%s'>", name);
        printf("<input type='hidden' name='score' value='%d'>", score);
        printf("<input type='hidden' name='q' value='%d'>", q + 1);
        
        // UPDATED: Button now uses CSS file class automatically
        printf("<br><button type='submit'>Next Question</button>");
        printf("</form>");

    } else {
        printf("<h1>Quiz Results</h1>");
        printf("<p style='text-align:center;'><b>Candidate:</b> %s</p>", name);
        printf("<p style='font-size:24px; text-align:center;'>Final Marks: <span style='color:#004d00; font-weight:bold;'>%d / 5</span></p>", score);
        
        if(score == 5) printf("<p style='color:green; text-align:center;'>Excellent! Pakistan Studies Expert!</p>");
        else if(score >= 3) printf("<p style='color:orange; text-align:center;'>Good Job!</p>");
        else printf("<p style='color:red; text-align:center;'>Keep studying!</p>");

        printf("<br><a href='../quiz_index.html'>Restart Quiz</a>");
    }

    printf("</div></body></html>");
    return 0;
}