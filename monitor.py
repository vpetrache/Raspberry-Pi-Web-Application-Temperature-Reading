def daily_songs(day):
    db = MySQLdb.connect("localhost","root","", "radio21")
    i= day + '%'
    cursor = db.cursor()
    sql = "SELECT artist, song, time from songs where time like ('%s') order by time desc" % \
          (i)

    try:
        cursor.execute(sql)
        results = cursor.fetchall()
        return results
    except:
        print "Error: unable to fetch data"

    db.close()
    
    <----
import csv
import time
import schedule
from datetime import datetime

def write_log():
    current_date = datetime.now().strftime('%Y-%m-%d')
    i = (current_date+'.csv')
    x = daily_songs(current_date)

    with open(i, 'wb') as csv_file:
        writer = csv.writer(csv_file)
        writer.writerow(['artists ', 'songs ', 'time'])
        writer.writerows(x)

schedule.every().hour.do(write_log)    
