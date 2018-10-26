import face_recognition
import cv2
import time



framenumber = 0
cap = cv2.VideoCapture("C:/Users/Marius/Downloads/opencvtest.mp4")


sz = (int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),
        int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))

fps = 20
fourcc = cv2.VideoWriter_fourcc(*'DIVX') 
vout = cv2.VideoWriter('output.mp4',fourcc , 20.0, sz)





def readFile(framenr):
    cap.set(cv2.CAP_PROP_POS_FRAMES, framenr)
    while cap.isOpened():
        global framenumber
        framenumber+=1
           
        ret, frame = cap.read()

        if not ret:
            vout.release()
            cap.release()
            cv2.destroyAllWindows()
        if framenumber % 30 == 0 and len(face_recognition.face_locations(frame))>1:    
            print("FACEEE")
            print(framenumber)
            foundFace(framenumber)
            break
        
                
                
def foundFace(framenr):
    cap.set(cv2.CAP_PROP_POS_FRAMES, framenr)
    start_time = time.time()
    newFrameNr = 0
    while( int(time.time() - start_time) < 5 ):
        newFrameNr+=1
        ret, frame = cap.read()
        if ret==True:
            vout.write(frame)

        else:
            readFile(framenr+newFrameNr)
            break
    readFile(framenr+newFrameNr)

        

readFile(1)


    

vout.release()
cap.release()
cv2.destroyAllWindows()