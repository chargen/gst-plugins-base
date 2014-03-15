/* GStreamer
 * Copyright (C) <2014> Wim Taymans <wim.taymans@gmail.com>
 *
 * gstmikey.h: various helper functions to manipulate mikey messages
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
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __GST_MIKEY_H__
#define __GST_MIKEY_H__

#include <gst/gst.h>

G_BEGIN_DECLS

typedef struct _GstMIKEYMessage GstMIKEYMessage;

/**
 * GST_MIKEY_VERSION:
 *
 * The supported MIKEY version 1.
 */
#define GST_MIKEY_VERSION 1

/**
 * GstMIKEYType:
 * @GST_MIKEY_TYPE_INVALID: Invalid type
 * @GST_MIKEY_TYPE_PSK_INIT: Initiator's pre-shared key message
 * @GST_MIKEY_TYPE_PSK_VERIFY: Verification message of a Pre-shared key message
 * @GST_MIKEY_TYPE_PK_INIT: Initiator's public-key transport message
 * @GST_MIKEY_TYPE_PK_VERIFY: Verification message of a public-key message
 * @GST_MIKEY_TYPE_DH_INIT: Initiator's DH exchange message
 * @GST_MIKEY_TYPE_DH_RESP: Responder's DH exchange message
 * @GST_MIKEY_TYPE_ERROR: Error message
 *
 * Different MIKEY data types.
 */
typedef enum
{
  GST_MIKEY_TYPE_INVALID    = -1,
  GST_MIKEY_TYPE_PSK_INIT   = 0,
  GST_MIKEY_TYPE_PSK_VERIFY = 1,
  GST_MIKEY_TYPE_PK_INIT    = 2,
  GST_MIKEY_TYPE_PK_VERIFY  = 3,
  GST_MIKEY_TYPE_DH_INIT    = 4,
  GST_MIKEY_TYPE_DH_RESP    = 5,
  GST_MIKEY_TYPE_ERROR      = 6
} GstMIKEYType;

/**
 * GstMIKEYPayloadType:
 * @GST_MIKEY_PT_LAST: Last payload
 * @GST_MIKEY_PT_KEMAC: Key data transport payload
 * @GST_MIKEY_PT_PKE: Envelope data payload
 * @GST_MIKEY_PT_DH: DH data payload
 * @GST_MIKEY_PT_SIGN: Signature payload
 * @GST_MIKEY_PT_T: Timestamp payload
 * @GST_MIKEY_PT_ID: ID payload
 * @GST_MIKEY_PT_CERT: Certificate Payload
 * @GST_MIKEY_PT_CHASH: Cert hash payload
 * @GST_MIKEY_PT_V: Verfication message payload
 * @GST_MIKEY_PT_SP: Security Policy payload
 * @GST_MIKEY_PT_RAND: RAND payload
 * @GST_MIKEY_PT_ERR: Error payload
 * @GST_MIKEY_PT_KEY_DATA: Key data sub-payload
 * @GST_MIKEY_PT_GEN_EXT: General Extension Payload

 * Different MIKEY Payload types.
 */
typedef enum
{
  GST_MIKEY_PT_LAST      = 0,
  GST_MIKEY_PT_KEMAC     = 1,
  GST_MIKEY_PT_PKE       = 2,
  GST_MIKEY_PT_DH        = 3,
  GST_MIKEY_PT_SIGN      = 4,
  GST_MIKEY_PT_T         = 5,
  GST_MIKEY_PT_ID        = 6,
  GST_MIKEY_PT_CERT      = 7,
  GST_MIKEY_PT_CHASH     = 8,
  GST_MIKEY_PT_V         = 9,
  GST_MIKEY_PT_SP        = 10,
  GST_MIKEY_PT_RAND      = 11,
  GST_MIKEY_PT_ERR       = 12,
  GST_MIKEY_PT_KEY_DATA  = 20,
  GST_MIKEY_PT_GEN_EXT   = 21
} GstMIKEYPayloadType;

/**
 * GstMIKEYPRFFunc:
 * @GST_MIKEY_PRF_MIKEY_1: MIKEY-1 PRF function
 *
 * The PRF function that has been/will be used for key derivation
 */
typedef enum
{
  GST_MIKEY_PRF_MIKEY_1  = 0
} GstMIKEYPRFFunc;

/**
 * GstMIKEYMapType:
 * @GST_MIKEY_MAP_TYPE_SRTP:
 *
 * Specifies the method of uniquely mapping Crypto Sessions to the security
 * protocol sessions.
 */
typedef enum
{
  GST_MIKEY_MAP_TYPE_SRTP  = 0
} GstMIKEYMapType;

/**
 * GstMIKEYMapSRTP:
 * @policy: The security policy applied for the stream with @ssrc
 * @ssrc: the SSRC that must be used for the stream
 * @roc: current rollover counter
 *
 * The Security policy Map item for SRTP
 */
typedef struct {
  guint8  policy;
  guint32 ssrc;
  guint32 roc;
} GstMIKEYMapSRTP;

typedef struct _GstMIKEYPayload GstMIKEYPayload;

/**
 * GstMIKEYPayloadClearFunc:
 * @payload: a #GstMIKEYPayload
 *
 * Function used to clear a payload
 */
typedef void (*GstMIKEYPayloadClearFunc) (GstMIKEYPayload *payload);

/**
 * GstMIKEYPayloadCopyFunc:
 * @payload: a #GstMIKEYPayload
 *
 * Function used to copy a payload
 */
typedef GstMIKEYPayload * (*GstMIKEYPayloadCopyFunc) (const GstMIKEYPayload *payload);

/**
 * GstMIKEYPayload:
 * @type: the payload type
 * @len: length of the payload
 * @clear_func: function to clear the payload
 * @copy_func: function to copy the payload
 *
 * Hold the common fields for all payloads
 */
struct _GstMIKEYPayload {
  GstMIKEYPayloadType type;
  guint len;
  GstMIKEYPayloadClearFunc clear_func;
  GstMIKEYPayloadCopyFunc copy_func;
};

GstMIKEYPayload *   gst_mikey_payload_new      (GstMIKEYPayloadType type);
GstMIKEYPayload *   gst_mikey_payload_copy     (const GstMIKEYPayload *payload);
gboolean            gst_mikey_payload_free     (GstMIKEYPayload *payload);

/**
 * GstMIKEYEncAlg:
 * @GST_MIKEY_ENC_NULL: no encryption
 * @GST_MIKEY_ENC_AES_CM_128: AES-CM using a 128-bit key
 * @GST_MIKEY_ENC_AES_KW_128: AES Key Wrap using a 128-bit key
 *
 * The encryption algorithm used to encrypt the Encr data field
 */
typedef enum
{
  GST_MIKEY_ENC_NULL        = 0,
  GST_MIKEY_ENC_AES_CM_128  = 1,
  GST_MIKEY_ENC_AES_KW_128  = 2
} GstMIKEYEncAlg;

/**
 * GstMIKEYMacAlg:
 * @GST_MIKEY_MAC_NULL: no authentication
 * @GST_MIKEY_MAC_HMAC_SHA_1_160: HMAC-SHA-1-160
 *
 * Specifies the authentication algorithm used
 */
typedef enum
{
  GST_MIKEY_MAC_NULL            = 0,
  GST_MIKEY_MAC_HMAC_SHA_1_160  = 1
} GstMIKEYMacAlg;

/**
 * GstMIKEYPayloadKEMAC:
 * @pt: the common #GstMIKEYPayload
 * @enc_alg: the #GstMIKEYEncAlg
 * @enc_len: the length of @enc_data
 * @enc_data: encryption data
 * @mac_alg: the #GstMIKEYMacAlg
 * @mac: the mac
 *
 * A structure holding the KEMAC payload
 */
typedef struct {
  GstMIKEYPayload pt;

  GstMIKEYEncAlg  enc_alg;
  guint16         enc_len;
  guint8         *enc_data;
  GstMIKEYMacAlg  mac_alg;
  guint8         *mac;
} GstMIKEYPayloadKEMAC;

gboolean               gst_mikey_payload_kemac_set   (GstMIKEYPayload *payload,
                                                      GstMIKEYEncAlg enc_alg,
                                                      guint16 enc_len, const guint8 *enc_data,
                                                      GstMIKEYMacAlg mac_alg, const guint8 *mac);

/**
 * GstMIKEYCacheType:
 * @GST_MIKEY_CACHE_NONE: The envelope key MUST NOT be cached
 * @GST_MIKEY_CACHE_ALWAYS: The envelope key MUST be cached
 * @GST_MIKEY_CACHE_FOR_CSB: The envelope key MUST be cached, but only
 *                           to be used for the specific CSB.
 *
 * The different cache types
 */
typedef enum
{
  GST_MIKEY_CACHE_NONE       = 0,
  GST_MIKEY_CACHE_ALWAYS     = 1,
  GST_MIKEY_CACHE_FOR_CSB    = 2
} GstMIKEYCacheType;

/**
 * GstMIKEYPayloadPKE:
 * @pt: the common #GstMIKEYPayload
 * @C: envelope key cache indicator
 * @data_len: length of @data
 * @data: the encrypted envelope key
 *
 * The Envelope data payload contains the encrypted envelope key that is
 * used in the public-key transport to protect the data in the Key data
 * transport payload.  The encryption algorithm used is implicit from
 * the certificate/public key used.
 */
typedef struct {
  GstMIKEYPayload pt;

  GstMIKEYCacheType C;
  guint16           data_len;
  guint8           *data;
} GstMIKEYPayloadPKE;

gboolean               gst_mikey_payload_pke_set     (GstMIKEYPayload *payload,
                                                      GstMIKEYCacheType C,
                                                      guint16 data_len, const guint8 *data);


/**
 * GstMIKEYTSType:
 * @GST_MIKEY_TS_TYPE_NTP_UTC: an NTP time in UTC timezone
 * @GST_MIKEY_TS_TYPE_NTP: an NTP time
 * @GST_MIKEY_TS_TYPE_COUNTER: a counter
 *
 * Specifies the timestamp type.
 */
typedef enum
{
  GST_MIKEY_TS_TYPE_NTP_UTC  = 0,
  GST_MIKEY_TS_TYPE_NTP      = 1,
  GST_MIKEY_TS_TYPE_COUNTER  = 2
} GstMIKEYTSType;

/**
 * GstMIKEYPayloadT:
 * @pt: the payload header
 * @type: a #GstMIKEYTSType
 * @ts_value: the timestamp value
 *
 * The timestamp payload carries the timestamp information
 */
typedef struct {
  GstMIKEYPayload pt;

  GstMIKEYTSType  type;
  guint8         *ts_value;
} GstMIKEYPayloadT;

gboolean   gst_mikey_payload_t_set   (GstMIKEYPayload *payload,
                                      GstMIKEYTSType type, const guint8 *ts_value);

/**
 * GstMIKEYPayloadSPParam:
 * @type: specifies the type of the parameter
 * @len: specifies the length of @val
 * @val: specifies the value of the parameter
 *
 * A Type/Length/Value field for security paramaters
 */
typedef struct {
  guint8  type;
  guint8  len;
  guint8 *val;
} GstMIKEYPayloadSPParam;

/**
 * GstMIKEYSecProto:
 * @GST_MIKEY_SEC_PROTO_SRTP:
 *
 * Specifies the security protocol
 */
typedef enum
{
  GST_MIKEY_SEC_PROTO_SRTP  = 0
} GstMIKEYSecProto;

/**
 * GstMIKEYSecSRTP:
 * @GST_MIKEY_SP_SRTP_ENC_ALG: Encryption algorithm
 * @GST_MIKEY_SP_SRTP_ENC_KEY_LEN: Session Encr. key length
 * @GST_MIKEY_SP_SRTP_AUTH_ALG: Authentication algorithm
 * @GST_MIKEY_SP_SRTP_AUTH_KEY_LEN: Session Auth. key length
 * @GST_MIKEY_SP_SRTP_SALT_KEY_LEN: Session Salt key length
 * @GST_MIKEY_SP_SRTP_PRF: SRTP Pseudo Random Function
 * @GST_MIKEY_SP_SRTP_KEY_DERIV_RATE: Key derivation rate
 * @GST_MIKEY_SP_SRTP_SRTP_ENC: SRTP encryption off/on, 0 if off, 1 if on
 * @GST_MIKEY_SP_SRTP_SRTCP_ENC: SRTCP encryption off/on, 0 if off, 1 if on
 * @GST_MIKEY_SP_SRTP_FEC_ORDER: sender's FEC order
 * @GST_MIKEY_SP_SRTP_SRTP_AUTH: SRTP authentication off/on, 0 if off, 1 if on
 * @GST_MIKEY_SP_SRTP_AUTH_TAG_LEN: Authentication tag length
 * @GST_MIKEY_SP_SRTP_SRTP_PREFIX_LEN: SRTP prefix length
 *
 * This policy specifies the parameters for SRTP and SRTCP
 */
typedef enum
{
  GST_MIKEY_SP_SRTP_ENC_ALG         =    0,
  GST_MIKEY_SP_SRTP_ENC_KEY_LEN     =    1,
  GST_MIKEY_SP_SRTP_AUTH_ALG        =    2,
  GST_MIKEY_SP_SRTP_AUTH_KEY_LEN    =    3,
  GST_MIKEY_SP_SRTP_SALT_KEY_LEN    =    4,
  GST_MIKEY_SP_SRTP_PRF             =    5,
  GST_MIKEY_SP_SRTP_KEY_DERIV_RATE  =    6,
  GST_MIKEY_SP_SRTP_SRTP_ENC        =    7,
  GST_MIKEY_SP_SRTP_SRTCP_ENC       =    8,
  GST_MIKEY_SP_SRTP_FEC_ORDER       =    9,
  GST_MIKEY_SP_SRTP_SRTP_AUTH       =   10,
  GST_MIKEY_SP_SRTP_AUTH_TAG_LEN    =   11,
  GST_MIKEY_SP_SRTP_SRTP_PREFIX_LEN =   12
} GstMIKEYSecSRTP;

/**
 * GstMIKEYPayloadSP:
 * @pt: the payload header
 * @policy: the policy number
 * @prot: the security protocol
 * @param_len:  the total length of the policy parameters for the
 *              specific security protocol
 * @params: array of #GstMIKEYPayloadPSParam
 *
 * The Security Policy payload defines a set of policies that apply to a
 * specific security protocol
 */
typedef struct {
  GstMIKEYPayload pt;

  guint policy;
  GstMIKEYSecProto proto;
  GArray *params;
} GstMIKEYPayloadSP;

gboolean            gst_mikey_payload_sp_set          (GstMIKEYPayload *payload,
                                                       guint policy, GstMIKEYSecProto proto);
guint               gst_mikey_payload_sp_get_n_params (const GstMIKEYPayload *payload);
const GstMIKEYPayloadSPParam *
                    gst_mikey_payload_sp_get_param    (const GstMIKEYPayload *payload, guint idx);
gboolean            gst_mikey_payload_sp_remove_param (GstMIKEYPayload *payload, guint idx);
gboolean            gst_mikey_payload_sp_add_param    (GstMIKEYPayload *payload,
                                                       guint8 type, guint8 len, const guint8 *val);

/**
 * GstMIKEYPayloadRAND:
 * @pt: the payload header
 * @len: the length of @rand
 * @rand: random values
 *
 * The RAND payload consists of a (pseudo-)random bit-string
 */
typedef struct {
  GstMIKEYPayload pt;

  guint8  len;
  guint8 *rand;
} GstMIKEYPayloadRAND;

gboolean   gst_mikey_payload_rand_set   (GstMIKEYPayload *payload,
                                         guint8 len, const guint8 *rand);

/**
 * GstMIKEYMessage:
 * @version: the version
 * @type: the #GstMIKEYType message type
 * @V: verify flag
 * @prf_func: a #GstMIKEYPRFFunc
 * @CSB_id: Identifies the Crypto Session Bundle
 * @map_type: a #GstMIKEYMapType
 * @map_info: map info array of type depending on @map_type
 * @payloads: the payload array of #GstMIKEYPayload
 *
 * Structure holding the information of the MIKEY message
 */
struct _GstMIKEYMessage
{
  guint8 version;
  GstMIKEYType type;
  gboolean V;
  GstMIKEYPRFFunc prf_func;
  guint32 CSB_id;
  GstMIKEYMapType map_type;
  GArray *map_info;
  GArray *payloads;
};

GstMIKEYMessage *           gst_mikey_message_new               (void);
GstMIKEYMessage *           gst_mikey_message_new_from_data     (gconstpointer data, gsize size);
GstMIKEYMessage *           gst_mikey_message_new_from_bytes    (GBytes *bytes);
void                        gst_mikey_message_free              (GstMIKEYMessage *msg);

GBytes *                    gst_mikey_message_to_bytes          (GstMIKEYMessage *msg);

gboolean                    gst_mikey_message_set_info          (GstMIKEYMessage *msg,
                                                                 guint8 version, GstMIKEYType type, gboolean V,
                                                                 GstMIKEYPRFFunc prf_func, guint32 CSB_id,
                                                                 GstMIKEYMapType map_type);
guint                       gst_mikey_message_get_n_cs          (const GstMIKEYMessage *msg);

/* SRTP crypto sessions */
const GstMIKEYMapSRTP *     gst_mikey_message_get_cs_srtp       (const GstMIKEYMessage *msg, guint idx);
gboolean                    gst_mikey_message_insert_cs_srtp    (GstMIKEYMessage *msg, gint idx,
                                                                 const GstMIKEYMapSRTP *map);
gboolean                    gst_mikey_message_replace_cs_srtp   (GstMIKEYMessage *msg, gint idx,
                                                                 const GstMIKEYMapSRTP *map);
gboolean                    gst_mikey_message_remove_cs_srtp    (GstMIKEYMessage *msg, gint idx);
gboolean                    gst_mikey_message_add_cs_srtp       (GstMIKEYMessage *msg,
                                                                 guint8 policy, guint32 ssrc, guint32 roc);

/* adding/retrieving payloads */
guint                       gst_mikey_message_get_n_payloads    (const GstMIKEYMessage *msg);
const GstMIKEYPayload *     gst_mikey_message_get_payload       (const GstMIKEYMessage *msg, guint idx);
const GstMIKEYPayload *     gst_mikey_message_find_payload      (const GstMIKEYMessage *msg,
                                                                 GstMIKEYPayloadType type, guint nth);
gboolean                    gst_mikey_message_remove_payload    (GstMIKEYMessage *msg, guint idx);
gboolean                    gst_mikey_message_insert_payload    (GstMIKEYMessage *msg, guint idx,
                                                                 GstMIKEYPayload *payload);
gboolean                    gst_mikey_message_add_payload       (GstMIKEYMessage *msg,
                                                                 GstMIKEYPayload *payload);
gboolean                    gst_mikey_message_replace_payload   (GstMIKEYMessage *msg, guint idx,
                                                                 GstMIKEYPayload *payload);


/* Key data transport payload (KEMAC) */
gboolean                    gst_mikey_message_add_kemac         (GstMIKEYMessage *msg,
                                                                 GstMIKEYEncAlg enc_alg,
                                                                 guint16 enc_len, const guint8 *enc_data,
                                                                 GstMIKEYMacAlg mac_alg, const guint8 *mac);
/* Envelope data payload (PKE) */
gboolean                    gst_mikey_message_add_pke           (GstMIKEYMessage *msg,
                                                                 GstMIKEYCacheType C,
                                                                 guint16 data_len, const guint8 *data);
/* DH data payload (DH) */
/* Signature payload (SIGN) */

/* Timestamp payload (T) */
gboolean                    gst_mikey_message_add_t             (GstMIKEYMessage *msg,
                                                                 GstMIKEYTSType type, const guint8 *ts_value);
gboolean                    gst_mikey_message_add_t_now_ntp_utc (GstMIKEYMessage *msg);
/* ID payload (ID) */
/* Certificate Payload (CERT) */
/* Cert hash payload (CHASH)*/
/* Ver msg payload (V) */
/* Security Policy payload (SP)*/
/* RAND payload (RAND) */
gboolean                    gst_mikey_message_add_rand          (GstMIKEYMessage *msg,
                                                                 guint8 len, const guint8 *rand);
gboolean                    gst_mikey_message_add_rand_len      (GstMIKEYMessage *msg, guint8 len);

/* Error payload (ERR) */
/* Key data sub-payload */
/* Key validity data */
/* General Extension Payload */


G_END_DECLS

#endif /* __GST_MIKEY_H__ */

