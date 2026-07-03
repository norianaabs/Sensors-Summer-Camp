import processing.serial.*;

Serial myPort;

int signal = 0;
int bpm = 0;
int ibi = 0;
int beat = 0;

int[] ecg = new int[1000];

void setup() {
  size(1000, 400);
  background(0);

  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 115200);
  myPort.bufferUntil('\n');
}

void draw() {

  // fade effect (ECG trail)
  fill(0, 25);
  rect(0, 0, width, height);

  stroke(0, 255, 0);
  noFill();

  beginShape();
  for (int i = 0; i < ecg.length - 1; i++) {
    ecg[i] = ecg[i + 1];
    vertex(i, map(ecg[i], 0, 1023, height, 0));
  }
  endShape();

  // heartbeat indicator
  if (beat == 1023) {
    fill(255, 0, 0);
    textSize(28);
    text("♥ BEAT", 20, 40);
  }

  // =========================
  // DISPLAY EXTRA DATA
  // =========================
  fill(0, 255, 0);
  textSize(16);
  text("BPM: " + bpm, 20, height - 60);

  fill(0, 200, 255);
  text("IBI: " + ibi + " ms", 20, height - 40);

  fill(150);
  text("Signal: " + signal, 20, height - 20);
}

void serialEvent(Serial myPort) {

  String data = myPort.readStringUntil('\n');

  if (data != null) {
    data = trim(data);
    String[] vals = split(data, ',');

    if (vals.length == 4) {
      signal = int(vals[0]);
      bpm = int(vals[1]);
      ibi = int(vals[2]);
      beat = int(vals[3]);

      ecg[ecg.length - 1] = signal;
    }
  }
}
