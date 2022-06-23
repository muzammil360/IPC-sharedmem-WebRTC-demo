#ifndef APPSRC_H
#define APPSRC_H

extern char *pSharedMem;

typedef struct {
	unsigned long  nFrame;
	size_t frameSizeBytes;
	int fps;
	char * pSharedMem;
} CustomData;


static void appsrc_get_data_cb(GstElement *appsrc, guint size, gpointer *userData) {
	gst_print ("appsrc_get_data_cb() starts\n");
	gst_print ("We need this many bytes: %d\n", size);


	CustomData *customUserData = (CustomData *)userData;

	// unpack the data for easy reading later on
	// unsigned long  nFrame = customUserData->nFrame;
	// size_t frameSizeBytes = customUserData->frameSizeBytes;
	// int fps = customUserData->fps;
	// TODO remove hardocded values and get form custom data
	static unsigned long  nFrame = 0;
	size_t frameSizeBytes = 800*600*3;
	int fps = 60;


	gst_print("nFrame: %ld\n", nFrame);
	gst_print("frameSizeBytes: %ld\n", frameSizeBytes);
	gst_print("fps: %d\n", fps);
	gst_print("pSharedMem: %p\n", pSharedMem);

	// Create a new empty buffer
 	GstBuffer *buffer = gst_buffer_new_and_alloc (frameSizeBytes);

	// set the timestamps
	GST_BUFFER_TIMESTAMP (buffer) = gst_util_uint64_scale (nFrame, GST_SECOND, fps);
	GST_BUFFER_DURATION (buffer) = gst_util_uint64_scale (1, GST_SECOND, fps);


	// get raw pointer to data 
	GstMapInfo map;
  	gst_buffer_map (buffer, &map, GST_MAP_WRITE);
    char *raw = (char *)map.data;


	// write data to buffer
	memcpy(raw, pSharedMem, frameSizeBytes); 

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
	gst_print("appsrc_get_data_cb() ends\n");

}



#endif /* APPSRC */
