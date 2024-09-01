#!/usr/bin/env python
# coding: utf-8

# In[ ]:


gs://dataproc-staging-asia-east1-853194707086-pb19ffdw/Youvegottofindwhatyoulove.txt
gs://dataproc-staging-asia-east1-853194707086-pb19ffdw/yellow_tripdata_2018-10.parquet


# ## Q1: Implement a program to calculate the average occurrences of each word

# In[1]:


from pyspark.sql import SparkSession
from pyspark import SparkConf
from pyspark.sql.functions import col
import pandas as pd


# In[2]:


conf = SparkConf()
conf.setMaster("yarn")
conf.set("spark.hadoop.fs.defaultFS", "10.140.0.4:9866")
conf.set("spark.hadoop.yarn.resourcemanager.hostname", "10.140.0.4")
spark = SparkSession.builder.config(conf=conf).getOrCreate()


# In[3]:


ori_txt = spark.read.text('gs://dataproc-staging-asia-east1-853194707086-pb19ffdw/Youvegottofindwhatyoulove.txt')
ori_txt = ori_txt.filter(col("value").isNotNull()).filter(col("value") != "")


# In[6]:


word = ori_txt.rdd.flatMap(lambda line: line.value.split())
word_counts = word.map(lambda w: (w.lower(), 1))                .reduceByKey(lambda count1, count2: count1 + count2)
top30 = word_counts.takeOrdered(30, lambda x: -x[1])
sentences = ori_txt.rdd.flatMap(lambda x: x.value.split(". ")).count()
avg_counts = [(word, count / sentences) for word, count in top30]
df_top30 = pd.DataFrame(avg_counts, columns =['word','avg_counts'])
display(df_top30)


# In[7]:


spark.stop()


# ## Q2: 2018/10 NYC Yellow Taxi trip

# In[11]:


import pandas as pd
import numpy as np
from pyspark.sql import SparkSession
from pyspark import SparkConf
from pyspark.sql.types import StructType, StructField, StringType, IntegerType,FloatType
from pyspark.sql.functions import when,col,avg


# In[12]:


conf = SparkConf()
conf.setMaster("yarn")
conf.set("spark.hadoop.fs.defaultFS", "10.140.0.4:9866")
conf.set("spark.hadoop.yarn.resourcemanager.hostname", "10.140.0.4")
spark = SparkSession.builder.config(conf=conf).getOrCreate()


# In[13]:


customSchema = StructType([
    StructField("VendorID", IntegerType(), True),  
    StructField("tpep_pickup_datetime", StringType(), True),  
    StructField("tpep_dropoff_datetime", StringType(), True),  
    StructField("passenger_count", FloatType(), True),  
    StructField("trip_distance", FloatType(), True),  
    StructField("RatecodeID", FloatType(), True),  
    StructField("store_and_fwd_flag", StringType(), True),  
    StructField("PULocationID", IntegerType(), True),
    StructField("DOLocationID", IntegerType(), True), 
    StructField("payment_type", StringType(), True),  
    StructField("fare_amount", FloatType(), True),  
    StructField("extra", FloatType(), True),  
    StructField("mta_tax", FloatType(), True),  
    StructField("tip_amount", FloatType(), True),  
    StructField("tolls_amount", FloatType(), True),  
    StructField("improvement_surcharge", FloatType(), True),
    StructField("total_amount", FloatType(), True),  
    StructField("congestion_surcharge", FloatType(), True),  
    StructField("airport_fee", FloatType(), True), 
])


# In[14]:


df=spark.read.parquet('gs://dataproc-staging-asia-east1-853194707086-pb19ffdw/yellow_tripdata_2018-10.parquet', header=True, schema=customSchema)
new_df = df.select("payment_type", "passenger_count","total_amount")

# payment_type
# 1= Credit card
# 2= Cash
credit_df = new_df.filter(col("payment_type") == "1.0")
cash_df = new_df.filter(col("payment_type") == "2.0")

credit_avg_df = credit_df.groupBy("passenger_count").agg(avg("total_amount").alias("Credit_avg_amount"))
cash_avg_df = cash_df.groupBy("passenger_count").agg(avg("total_amount").alias("Cash_avg_amount"))

joined_df = credit_avg_df.join(cash_avg_df, "passenger_count")
filtered_joined_df = joined_df.filter(col("passenger_count") >= 1).filter(col("passenger_count") <= 4).orderBy(col("passenger_count"), ascending=True)
filtered_joined_df.show()


# In[ ]:




