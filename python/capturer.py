import cv2
import time


class Capturer:
    def __init__(self):
        self.open = True
        self.device_index = 0
        self.video_cap = cv2.VideoCapture(self.device_index)
        self.start_time = time.time()

    def capture(self):
        while (self.open == True):
            ret, frame = self.video_cap.read()
            if ret == True:
                cv2.imshow('frame', frame)
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
            else:
                break

        self.video_cap.release()
        cv2.destroyAllWindows()

    def stop(self):
        if self.open == True:
            self.open = False
            self.video_cap.release()


if __name__ == "__main__":
    cap = Capturer()
    cap.capture()
