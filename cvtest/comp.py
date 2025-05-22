import cv2

s1 = cv2.imread('c1.jpg')
s2 = cv2.imread("c2.jpg")
diff = cv2.absdiff(s1, s2)
r,thre = cv2.threshold(diff, 120, 255, cv2.THRESH_BINARY)
gray = cv2.cvtColor(thre,cv2.COLOR_BGR2GRAY) # Gray 변환
cont,r1=cv2.findContours(gray,cv2.RETR_EXTERNAL ,cv2.CHAIN_APPROX_SIMPLE)

#cv2.imshow('s1',s1)
#cv2.imshow('s2',s2)
#cv2.imshow("diff", diff)
#cv2.imshow("Canny", cann)
for a in cont:
    x,y,w,h = cv2.boundingRect(a)
    cv2.rectangle(thre, (x,y), (x+w,y+h), (0,0,255), 2)
cv2.imshow("Threshold", thre)
    
#cv2.imshow("Contours", cont)

cv2.waitKey()
