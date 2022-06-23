#ifndef APPSRC_H
#define APPSRC_H

extern char *pSharedMem;
extern const size_t bufferSize;
extern const int fps;

// typedef struct {
// 	unsigned long  nFrame;
// 	size_t frameSizeBytes;
// 	int fps;
// 	char * pSharedMem;
// } CustomData;


static void appsrc_get_data_cb(GstElement *appsrc, guint size, gpointer *userData) {


	static unsigned long  nFrame = 0;

	// Create a new empty buffer
 	GstBuffer *buffer = gst_buffer_new_and_alloc (bufferSize);

	// set the timestamps
	GST_BUFFER_TIMESTAMP (buffer) = gst_util_uint64_scale (nFrame, GST_SECOND, fps);
	GST_BUFFER_DURATION (buffer) = gst_util_uint64_scale (1, GST_SECOND, fps);


	// get raw pointer to data 
	GstMapInfo map;
  	gst_buffer_map (buffer, &map, GST_MAP_WRITE);
    char *raw = (char *)map.data;


	// write data to buffer
	memcpy(raw, pSharedMem, bufferSize); 

	// push to appsrc by emiting signal 
	GstFlowReturn ret;
    g_signal_emit_by_name (appsrc, "push-buffer", buffer, &ret);


	if (ret != GST_FLOW_OK) {
        gst_printerr ("error in pushing data into the pipeline\n");
	}

	// increase the nFrame count 
	nFrame++;

	// free the buffer since we are done with it 
	gst_buffer_unmap (buffer, &map);
    gst_buffer_unref (buffer);

}



#endif /* APPSRC */
