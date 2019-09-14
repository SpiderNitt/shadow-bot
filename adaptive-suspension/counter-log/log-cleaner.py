import pandas as pd

def retTime(junkTime):
    time = junkTime[7:]
    return time

if __name__ == "__main__":
    filename = '2-log.txt'
    cleanFilename = '2-clean-log.csv'
    data = pd.read_csv(filename, sep=' ')
    time = data.iloc[:, 0]
    counter = data.iloc[:, 2]
    time = time.apply(retTime)

    cleanData = list(zip(time, counter))
    logData = pd.DataFrame(data=cleanData, columns=['Time', 'Counter'])
    logData.to_csv(cleanFilename, index=False)
    #print(logData.head)





