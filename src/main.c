#include <zephyr/types.h>

#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>

static uint8_t broadcast_data[] = {0x0};

static const struct bt_data ad[] = {
    BT_DATA(BT_DATA_MANAFACTURER_DATA, broadcast_data, 1),
};

int main(void)
{
    int err;

    err = bt_enable(NULL);
    if(err)
    {
        printk("Bluetooth init failed!\r\n");
        return 1;
    }

    while(1)
    {
        k_msleep(1000);

        err = bt_le_adv_start(BT_LE_ADV_NCONN, ad, ARRAY_SIZE(ad), NULL, 0);

        if(err)
        {
            printk("Advertising start failed!\r\n");
            return 1;
        }

        k_msleep(1000);

        err = bt_le_adv_stop();

        if(err)
        {
            printk("Advertising stop failed!\r\n");
            return 1;
        }

        broadcast_data[0]++;
    } 

    return 0;
}