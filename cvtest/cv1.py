#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  cv1.py
#  
#  Copyright 2025  <pi@AI105>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  
import cv2

s_img = cv2.imread("c1.jpg")
#c_img = cv2.GaussianBlur(s_img,(7,7), 0 )
#r,c_img = cv2.threshold(s_img, 120, 255, cv2.THRESH_BINARY)
c_img = cv2.Canny(s_img, 100, 200)

cv2.imshow("",s_img)
cv2.imshow("Converted",c_img)
cv2.waitKey(0)




