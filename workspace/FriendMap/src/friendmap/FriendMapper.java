package friendmap;
import java.io.IOException;
import java.util.*;
	
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.util.*;

import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.Reducer.Context;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class FriendMapper {

	public static class FooMapper extends Mapper<LongWritable, Text,Text,IntWritable>{
		private final static IntWritable yes = new IntWritable(1);
	    private Text word = new Text();
 
	
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
       String [] input=value.toString().split("\t");
       ArrayList<String> friends=new ArrayList<String> (100);
       if (input.length > 1) {
           StringTokenizer tokenizer = new StringTokenizer(input[1], ",");
           while (tokenizer.hasMoreTokens()) {
        	   String friend = tokenizer.nextToken();
        	   friends.add(friend);
           }
           for(int i=0;i<friends.size();i++)
        	   for(int j=i+1;j<friends.size();j++){
        		   word.set(new Text(friends.get(i)+ ","+friends.get(j)));
           			context.write(word, yes);}
      }
  }
}
	

  public static class FriendReducer
       extends Reducer<Text, IntWritable, Text, IntWritable> {
   // Map<String,Integer> map = new HashMap<String,Integer>();
    IntWritable result=new IntWritable();

    public void reduce(Text key,Iterable<IntWritable> friends,
                       Context context
                       ) throws IOException, InterruptedException {
    	int sum=0;
    	for(IntWritable val : friends){
    	sum += val.get();
    	}
    	result.set(sum);

    	context.write(key,result);
  }
  }

  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "friend count");
    job.setJarByClass(FriendMapper.class);
    job.setMapperClass(FooMapper.class);
    job.setCombinerClass(FriendReducer.class);
    job.setReducerClass(FriendReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}