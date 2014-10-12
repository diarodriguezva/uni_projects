import pickle

class medianFilter:
    def __init__(self,maxlength):
        self.list=[]
        self.maxlength=maxlength
    def filter(self,x):
        if len(self.list)>=self.maxlength:
            self.list.pop(0)
        self.list.append(x)

        list_sorted=list(self.list)
        list_sorted.sort()

        if len(list_sorted)==0:
            return 0
        return list_sorted[len(list_sorted)/2]



class ball:
    def __init__(self,color):
        self.color=color
        f = open(color + ".pyo", 'r')
        self.histogram=pickle.load(f)
        f.close()
        self.r_filter=medianFilter(5)
        self.x_filter=medianFilter(5)
        self.y_filter=medianFilter(5)


    def filter2D(self,r,x,y):
        r=self.r_filter.filter(r)
        x=self.x_filter.filter(x)
        y=self.y_filter.filter(y)
        return r,x,y