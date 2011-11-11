/* GStreamer
 * Copyright (C) <2005> Wim Taymans <wim@fluendo.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GST_RTP_BASE_PAYLOAD_H__
#define __GST_RTP_BASE_PAYLOAD_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define GST_TYPE_RTP_BASE_PAYLOAD \
        (gst_rtp_base_payload_get_type())
#define GST_RTP_BASE_PAYLOAD(obj) \
        (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_RTP_BASE_PAYLOAD,GstRTPBasePayload))
#define GST_RTP_BASE_PAYLOAD_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_RTP_BASE_PAYLOAD,GstRTPBasePayloadClass))
#define GST_RTP_BASE_PAYLOAD_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_RTP_BASE_PAYLOAD, GstRTPBasePayloadClass))
#define GST_IS_RTP_BASE_PAYLOAD(obj) \
        (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_RTP_BASE_PAYLOAD))
#define GST_IS_RTP_BASE_PAYLOAD_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_RTP_BASE_PAYLOAD))
#define GST_RTP_BASE_PAYLOAD_CAST(obj) \
        ((GstRTPBasePayload*)(obj))

typedef struct _GstRTPBasePayload GstRTPBasePayload;
typedef struct _GstRTPBasePayloadPrivate GstRTPBasePayloadPrivate;
typedef struct _GstRTPBasePayloadClass GstRTPBasePayloadClass;

/**
 * GST_RTP_BASE_PAYLOAD_SINKPAD:
 * @payload: a #GstRTPBasePayload
 *
 * Get access to the sinkpad of @payload.
 */
#define GST_RTP_BASE_PAYLOAD_SINKPAD(payload) (GST_RTP_BASE_PAYLOAD (payload)->sinkpad)
/**
 * GST_RTP_BASE_PAYLOAD_SRCPAD:
 * @payload: a #GstRTPBasePayload
 *
 * Get access to the srcpad of @payload.
 */
#define GST_RTP_BASE_PAYLOAD_SRCPAD(payload)  (GST_RTP_BASE_PAYLOAD (payload)->srcpad)

/**
 * GST_RTP_BASE_PAYLOAD_PT:
 * @payload: a #GstRTPBasePayload
 *
 * Get access to the configured payload type of @payload.
 */
#define GST_RTP_BASE_PAYLOAD_PT(payload)  (GST_RTP_BASE_PAYLOAD (payload)->pt)
/**
 * GST_RTP_BASE_PAYLOAD_MTU:
 * @payload: a #GstRTPBasePayload
 *
 * Get access to the configured MTU of @payload.
 */
#define GST_RTP_BASE_PAYLOAD_MTU(payload) (GST_RTP_BASE_PAYLOAD (payload)->mtu)

struct _GstRTPBasePayload
{
  GstElement element;

  /*< private >*/
  GstPad  *sinkpad;
  GstPad  *srcpad;

  guint32  ts_base;
  guint16  seqnum_base;

  gchar   *media;
  gchar   *encoding_name;
  gboolean dynamic;
  guint32  clock_rate;

  gint32   ts_offset;
  guint32  timestamp;
  gint16   seqnum_offset;
  guint16  seqnum;
  gint64   max_ptime;
  guint    pt;
  guint    ssrc;
  guint    current_ssrc;
  guint    mtu;

  GstSegment segment;

  guint64  min_ptime;

  /*< private >*/
  GstRTPBasePayloadPrivate *priv;

  union  {
    struct {
      guint64 ptime; /* in ns */
      guint64 ptime_multiple; /* in ns */
    } ABI;
    gpointer _gst_reserved[GST_PADDING - (sizeof(guint64)/sizeof(gpointer)) - 1];
  } abidata;
};

/**
 * GstRTPBasePayloadClass:
 * @parent_class: the parent class
 * @set_caps: configure the payloader
 * @handle_buffer: process data
 * @handle_event: custom event handling
 * @get_caps: get desired caps
 *
 * Base class for audio RTP payloader.
 */
struct _GstRTPBasePayloadClass
{
  GstElementClass parent_class;

  /* query accepted caps */
  GstCaps *     (*get_caps)             (GstRTPBasePayload *payload, GstPad * pad, GstCaps * filter);
  /* receive caps on the sink pad, configure the payloader. */
  gboolean      (*set_caps)             (GstRTPBasePayload *payload, GstCaps *caps);

  /* handle a buffer, perform 0 or more gst_rtp_base_payload_push() on
   * the RTP buffers. This function takes ownership of the buffer. */
  GstFlowReturn (*handle_buffer)        (GstRTPBasePayload *payload,
                                         GstBuffer *buffer);
  gboolean      (*handle_event)         (GstRTPBasePayload *payload, GstEvent * event);

  /*< private >*/
  gpointer _gst_reserved[GST_PADDING];
};

GType           gst_rtp_base_payload_get_type           (void);

void            gst_rtp_base_payload_set_options        (GstRTPBasePayload *payload,
                                                         const gchar *media,
                                                         gboolean dynamic,
                                                         const gchar *encoding_name,
                                                         guint32 clock_rate);

gboolean        gst_rtp_base_payload_set_outcaps        (GstRTPBasePayload *payload,
                                                         const gchar *fieldname, ...);

gboolean        gst_rtp_base_payload_is_filled          (GstRTPBasePayload *payload,
                                                         guint size, GstClockTime duration);

GstFlowReturn   gst_rtp_base_payload_push               (GstRTPBasePayload *payload,
                                                         GstBuffer *buffer);

GstFlowReturn   gst_rtp_base_payload_push_list          (GstRTPBasePayload *payload,
                                                         GstBufferList *list);

G_END_DECLS

#endif /* __GST_RTP_BASE_PAYLOAD_H__ */
