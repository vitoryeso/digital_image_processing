import cv2 as cv
import imutils
import numpy as np

def gray_to_rgbchannel(img, channel=1):
    prov = np.zeros((img.shape) + (3,), np.double)
    prov[:, :, channel] = img
    print(prov)
    return prov 


video = cv.VideoCapture()
address = "http://192.168.0.13:8080/video"
video.open(address)

blur_lv = 3
laplacian_lv = 3
while True:
    check, frame = video.read()
    gray_img = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    gray_img = cv.resize(gray_img, (640, 480))
    gray_img = imutils.rotate_bound(gray_img, 90)
    

    # img = cv.cvtColor(frame, cv.COLOR_RGB2BGR)
    
    blured_img = cv.GaussianBlur(gray_img, (blur_lv, blur_lv), 0)

    grad_x = cv.Sobel(blured_img, cv.CV_64F, 1, 0, ksize=3)
    grad_y = cv.Sobel(blured_img, cv.CV_64F, 0, 1, ksize=3)

    laplacian_img = cv.Laplacian(blured_img, cv.CV_64F, ksize=laplacian_lv)

    abs_grad_x = cv.convertScaleAbs(grad_x)
    abs_grad_y = cv.convertScaleAbs(grad_y)

    grad = cv.addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0)
    #grad = cv.addWeighted(grad_x, 0.5, grad_y, 0.5, 0)

    cv.imshow('grad_x', grad_x)
    cv.imshow('grad_y', grad_y)
    cv.imshow('sobel img', grad)
    cv.imshow('r', gray_to_rgbchannel(laplacian_img, 0))
    cv.imshow('g', gray_to_rgbchannel(laplacian_img, 1))
    cv.imshow('b', gray_to_rgbchannel(laplacian_img, 2))
    c = cv.waitKey(1)
    if c == 27:
        break
    if c == ord('h'):
        if blur_lv < 5:
            blur_lv = 3
        else:
            blur_lv -= 4
    if c == ord('l'):
        if blur_lv > 57:
            blur_lv = 57
        else:
            blur_lv += 4
    if c == ord('j'):
        if laplacian_lv < 5:
            laplacian_lv = 3
        else:
            laplacian_lv -= 4
    if c == ord('k'):
        if laplacian_lv > 57:
            laplacian_lv = 57
        else:
            laplacian_lv += 4

video.release()
cv.destroyAllWindows()
    
