import serial
import time
import matplotlib.pyplot as plt

ser = serial.Serial('COM13', 9600, timeout=1)

time.sleep(15)  # 🔴 allow Arduino reboot

times = []
errors = []

start_time = time.time()

print("Collecting data... Press Ctrl+C to stop")

try:
    while True:
        line = ser.readline().decode('utf-8', errors='ignore').strip()

        if ',' in line:
            parts = line.split(',')

            if len(parts) == 2:
                try:
                    t = int(parts[0]) / 1000.0
                    err = float(parts[1])

                    times.append(t)
                    errors.append(err)

                    print(f"t={t:.2f}s error={err}")

                except:
                    pass

except KeyboardInterrupt:
    print("Stopped.")

# Compute IAE
iae = 0
for i in range(1, len(times)):
    dt = times[i] - times[i-1]
    iae += abs(errors[i]) * dt

print(f"\nIntegral of Absolute Error (IAE): {iae:.2f}")

plt.plot(times, errors)
plt.xlabel("Time (s)")
plt.ylabel("Error")
plt.title("Error vs Time")
plt.grid()
plt.show()