import cv2 as cv
import numpy as np




    
img = cv.imread("Testphoto.jpg") #image here
greyImage = cv.cvtColor(img, cv.COLOR_RGB2GRAY)

cv.imshow('Grayscale',greyImage)

imgSize = greyImage.shape
print("Image Size: ",imgSize)

#(r-u)^T K^-1 (r-u)
uGlob = np.mean(greyImage)
K = np.cov(greyImage)
kInv = np.linalg.inv(K)
    
RXImage = np.array([])
colVector = np.array([])
for i in greyImage:

    for r in i:
        rU = r - uGlob
        rUTrans = np.transpose(rU)
    
        RXDVal = rUTrans * kInv * rU # may need to use np dot product func due to matrix multiplication

        colVector=np.hstack(RXDVal)
        
    print("Current column: ",i)
    RXImage=np.vstack(colVector)
    colVector = np.array([])

#cv.waitkey(0)
cv.imshow('RXD Global', RXImage)
    