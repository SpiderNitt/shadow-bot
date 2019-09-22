import cv2

def devices_check():
	index = 0
	arr = []
	while True:
		cap = cv2.VideoCapture(index)
		if not cap.read()[0]:
		    break
		else:
		    arr.append(index)
		cap.release()
		index += 1
	print('Number of devices =',len(arr))

def image_capture():
	cap = cv2.VideoCapture(1)
	ret,frame = cap.read()
	cv2.imshow('frame',frame)

if __name__ == "__main__":
	devices_check()
	while True:
		image_capture()
		if cv2.waitKey(1) & 0xFF == ord('q'):
			break
