#include <alsa/asoundlib.h>

// initialis the sound card
static void sinit(snd_mixer_t **handle, snd_mixer_elem_t **elem, snd_mixer_selem_id_t **mixer_id)
{
    // Open an empty mixer
    snd_mixer_open(handle, SND_MIXER_ELEM_SIMPLE);
    // Open the default interface, see: $ cat /proc/asound/cards
    // alternatively, this can be "hw:0" instead of "default"
    snd_mixer_attach(*handle, "default");
    snd_mixer_selem_register(*handle, NULL, NULL);

    // Load the mixer elements
    snd_mixer_load(*handle);

    snd_mixer_selem_id_alloca(mixer_id);
    snd_mixer_selem_id_set_index(*mixer_id, 0);
    // PCM is the default interface, see: $ amixer
    snd_mixer_selem_id_set_name(*mixer_id, "PCM");

    *elem = snd_mixer_find_selem(*handle, *mixer_id);
}

// close the souncard
static void sclose(snd_mixer_t **handle)
{
    // detach a previously attached HCTL to an opened mixer freeing all related resources.
    snd_mixer_detach(*handle, "default");
    // close a mixer and free all related resources.
    snd_mixer_close(*handle);
}

void set_volume(const int dB_value)
{
    snd_mixer_t *handle;            // ALSA mixer sound card handle
    snd_mixer_elem_t *elem;         // ALSA mixer
    snd_mixer_selem_id_t *mixer_id; // ALSA mixer simple element

    sinit(&handle, &elem, &mixer_id);

    // sets the volume for all the channels to the assigned dV value
    snd_mixer_selem_set_playback_dB_all(elem, dB_value, 0);

    sclose(&handle);
}

// get the system volume in dB
int get_volume()
{
    snd_mixer_t *handle;            // ALSA mixer sound card handle
    snd_mixer_elem_t *elem;         // ALSA mixer
    snd_mixer_selem_id_t *mixer_id; // ALSA mixer simple element

    sinit(&handle, &elem, &mixer_id);

    long volume;
    snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_FRONT_LEFT, &volume);

    sclose(&handle);

    return (int)volume;
}

// get the system min and max volume in dB
void get_range(int *min, int *max)
{
    if (!min)
    {
        printf("NULL pointer argument: min");
        return;
    }

    if (!max)
    {
        printf("NULL pointer argument: max");
        return;
    }

    long lmin, lmax;

    snd_mixer_t *handle;            // ALSA mixer sound card handle
    snd_mixer_elem_t *elem;         // ALSA mixer
    snd_mixer_selem_id_t *mixer_id; // ALSA mixer simple element

    sinit(&handle, &elem, &mixer_id);

    // get min and max playback volume in dB
    snd_mixer_selem_get_playback_volume_range(elem, &lmin, &lmax);

    *min = (int)lmin;
    *max = (int)lmax;

    sclose(&handle);
}