setwd("H:/faculdade/com backup/00Material da Faculdade/6semestre/instrumentacao/winkel/dadoscapturados")
d = read.table("rcomserial.tsv",header=TRUE, sep = "\t", dec = ".", quote="", na.strings = "NA")
help(hist)
par(mfrow = c(3,3))
hist(d$AccelX,xlab="Acelerometro X",main="",ylab="")
hist(d$AccelY,xlab="Acelerometro Y",main="",ylab="")
hist(d$AccelZ,xlab="Acelerometro Z",main="",ylab="")
hist(d$gyroX,xlab="Giroscópio X",main="",ylab="")
hist(d$gyroY,xlab="Giroscópio Y",main="",ylab="")
hist(d$gyroZ,xlab="Giroscópio Z",main="",ylab="")
hist(d$magnetX,xlab="Magnetômetro X",main="",ylab="")
hist(d$magnetY,xlab="Magnetômetro Y",main="",ylab="")
hist(d$magnetZ,xlab="Magnetômetro Z",main="",ylab="")

par(mfrow = c(1,1))
title("Histograma GY-87")

shapiro.test(d$AccelX[1:5000])
shapiro.test(d$AccelY[1:5000])
shapiro.test(d$AccelZ[1:5000])
shapiro.test(d$gyroX[1:5000])
shapiro.test(d$gyroY[1:5000])
shapiro.test(d$gyroZ[1:5000])
shapiro.test(d$magnetX[1:5000])
shapiro.test(d$magnetY[1:5000])
shapiro.test(d$magnetZ[1:5000])



help(plot)
par(mfrow = c(3,1))
plot(d$AccelX,type="l")
plot(d$AccelY,type="l")
plot(d$AccelZ,type="l")
plot(d$gyroX,type="l")
plot(d$gyroY,type="l")
plot(d$gyroZ,type="l")
plot(d$magnetX,type="l")
plot(d$magnetY,type="l")
plot(d$magnetZ,type="l")
par(mfrow = c(1,1))
title("Plote GY-87")
