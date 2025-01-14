with open('sampleLogFile.txt') as f:
    for line in f:
        if "INFO" in line and "2024-02" in line:
            print(line.strip())
