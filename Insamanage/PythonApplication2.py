import sys
import re

f=open('G1101.TXT','rb')


d=open('g1101result2.txt','w')

for i in range(0,80941,373):
    f.seek(i,0)
    d.write('{사번:%s},'%f.read(8).decode('EUC-KR'))
    f.seek(i+8,0)
    d.write('{이름:%s},'%f.read(8).decode('EUC-KR'))
    f.seek(i+16,0)
    d.write('{주민번호:%s},'%str(f.read(13).decode('EUC-KR')))
    f.seek(i+29,0)
    d.write('{주소:%s},'%f.read(72).decode('EUC-KR'))
    f.seek(i+101,0)
    d.write('{전화번호:%s},'%f.read(13).decode('EUC-KR'))
    f.seek(i+114,0)
    d.write('{빈칸:%s},'%f.read(49).decode('EUC-KR'))
    f.seek(i+163,0)
    d.write('{전화번호:%s},'%f.read(12).decode('EUC-KR'))
    f.seek(i+175,0)
    d.write('{급여구분:%s},'%f.read(1).decode('EUC-KR'))
    f.seek(i+176,0)
    d.write('{입사경위:%s},'%f.read(1).decode('EUC-KR'))
    f.seek(i+177,0)
    d.write('{코드:%s},'%f.read(1).decode('EUC-KR'))
    f.seek(i+180,0)
    d.write('{코드2:%s},'%f.read(1).decode('EUC-KR'))
    f.seek(i+181,0)
    d.write('{입사일자:%s},'%f.read(8).decode('EUC-KR'))
    f.seek(i+189,0)
    d.write('{발령일자:%s},'%f.read(8).decode('EUC-KR'))
    f.seek(i+197,0)
    d.write('{승진일자:%s},'%f.read(8).decode('EUC-KR'))
    f.seek(i+205,0)
    d.write('{휴직일자:%s},'%f.read(8).decode('EUC-KR'))
    f.seek(i+213,0)
    d.write('{복직일자:%s},'%f.read(8).decode('EUC-KR'))
    f.seek(i+221,0)
    d.write('{퇴직일자:%s},'%f.read(8).decode('EUC-KR'))
    f.seek(i+229,0)
    d.write('{부서:%s},'%f.read(4).decode('EUC-KR'))
    f.seek(i+235,0)
    d.write('{직급:%s},'%f.read(3).decode('EUC-KR'))
    f.seek(i+238,0)
    d.write('{코드4:%s},'%f.read(45).decode('EUC-KR'))
    f.seek(i+283,0)
    d.write('{키(cm):%s},'%f.read(3).decode('EUC-KR'))
    f.seek(i+286,0)
    d.write('{체중(kg:%s},'%f.read(3).decode('EUC-KR'))
    f.seek(i+289,0)
    d.write('{시력(좌):%s.%s},'%(f.read(1).decode('EUC-KR'),f.read(1).decode('EUC-KR')))
    f.seek(i+291,0)
    d.write('{시력(우):%s.%s},'%(f.read(1).decode('EUC-KR'),f.read(1).decode('EUC-KR')))
    f.seek(i+293,0)
    d.write('{혈액형:%s},'%f.read(2).decode('EUC-KR'))
    f.seek(i+303,0)
    d.write('{군필:%s}'%f.read(20).decode('EUC-KR'))
    f.seek(i+305,0)
    d.write('{군별:%s},{계급:%s},'%(f.read(1).decode('EUC-KR'),f.read(1).decode('EUC-KR')))
        
    f.seek(i+322,0)
    d.write('{코드6:%s},'%f.read(15).decode('EUC-KR'))
    
    
    
    
    f.seek(i+337,0)
    d.write('{코드7:%s},'%f.read(30).decode('EUC-KR'))
    f.seek(i+367,0)
    d.write('{공제flag:%s}'%f.read(6).decode('EUC-KR'))
    f.seek(i+373,0)
    d.write('\n')







d.flush()
d.close()
f.close()